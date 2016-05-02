/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2010,2011,2012 Adrien Boussicault, Marc Zipstein
 *
 *
 *    This Library is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This Library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this Library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "MLV_net.h"

#include "warning_error.h"

#include "memory_management.h"
#include "MLV_time.h"  //TODO : Remove

#include "data_structure.h"
#include "tree_map.h"

#include "platform.h"
#include <stdint.h>
#include <assert.h>

#if defined( OS_WINDOWS )
#	include <SDL/SDL_net.h>
#elif defined( OS_APPLE )
#	include <SDL_net/SDL_net.h>
#else
#	include <SDL/SDL_net.h>
#endif
#include "SDL/SDL_thread.h"

#include "sdlinitialisation.h"
#include "window.h"

extern DataMLV* MLV_data;

int MLV_init_network(){
	initialise_sdl();
	return SDLNet_Init();
}

void MLV_free_network(){
	SDLNet_Quit();
	if( ! window_is_open() ){
		free_sdl();
	}
}

typedef struct _Human_ip {
	char* host;
	unsigned int ip[4];
	unsigned int port;
} Human_ip;


typedef enum {
	MLV_NET_P_NONE = MLV_NET_NONE, 
	MLV_NET_P_TEXT = MLV_NET_TEXT, 
	MLV_NET_P_INTEGER = MLV_NET_INTEGER,
	MLV_NET_P_REAL = MLV_NET_REAL,
	MLV_NET_P_SERVER_FULL = 4,
	MLV_NET_P_ID_AFFECTATION = 5,
	MLV_NET_P_LOGIN_DECLARATION = 6,
	MLV_NET_P_LOGIN_YET_USED = 7,
	MLV_NET_P_NEW_ID = 8,

	MLV_NET_P_ID_REQUEST = 9,
	MLV_NET_P_ID_ANSWER = 10,
	MLV_NET_P_NICKNAME_REQUEST = 11,
	MLV_NET_P_NICKNAME_ANSWER = 12
} MLV_Net_protocol;

struct _MLV_Server_connection {
	IPaddress ip;
	TCPsocket socket;

	SDLNet_SocketSet set;

	char* nickname;
	Uint16 nickname_id;

	MLV_TreeMap* nickname_to_id;
	MLV_TreeMap* id_to_nickname;
};

typedef struct {
	TCPsocket socket;
	Uint16 id;
} Net_client;

struct _MLV_Server {
	IPaddress ip;
	TCPsocket home;

	int max_conection;
	int port;
	int is_on;

	SDL_mutex * mutex;

	SDLNet_SocketSet set;
	Net_client * clients;
	size_t nb_client;

	MLV_TreeMap* id_to_socket;

	MLV_TreeMap* nickname_to_id;
	MLV_TreeMap* id_to_nickname;
	int max_id_client;
};


void convert_sdl_ip_to_human_ip( const IPaddress * ip, Human_ip * human_ip ){
	// Resolve the ip address
	const char * host;
	host = SDLNet_ResolveIP( ip );
	if( host ){
		human_ip->host = strdup( host ); 
	}else{
		human_ip->host = NULL;
	}

	/* perform a byte endianess correction for the next printf */
	Uint32 ipaddr = SDL_SwapBE32( ip->host );

	/* output the IP address nicely */
	human_ip->ip[0] = ipaddr>>24;
	human_ip->ip[1] = (ipaddr>>16)&0xff;
	human_ip->ip[2] = (ipaddr>>8)&0xff;
	human_ip->ip[3] = ipaddr&0xff;

	human_ip->port = (Uint32) ip->port;
};

void init_human_ip( Human_ip * ip ){
	ip->host=NULL;
	ip->ip[0] = 0;
	ip->ip[1] = 0;
	ip->ip[2] = 0;
	ip->ip[3] = 0;
	ip->port = 0;
}

void free_human_ip( Human_ip * ip ){
	free( ip->host );
	init_human_ip( ip );
}

void fprint_ip( FILE* stream, IPaddress * ip ){
	Human_ip human_ip;
	convert_sdl_ip_to_human_ip( ip, &human_ip );
	fprintf(
		stream, "ip=%d.%d.%d.%d (%s), port=%d", 
		human_ip.ip[0], human_ip.ip[1], human_ip.ip[2], 
		human_ip.ip[3], 
		human_ip.host ? human_ip.host : "?",
		human_ip.port 
	);
}

int cmp_str( void* v1, void * v2  ){
	return strcmp( (const char *)v1, (const char*) v2 );
}

int cmp_int( void* v1, void * v2  ){
	return (*(int *)v1) - (*(int *) v2 );
}

MLV_Server * allocate_mlv_server( unsigned int port, int max_conection ){
	MLV_Server* server = MLV_MALLOC( 1, MLV_Server );
	if( !server ){
		ERROR("Unable to allocate MLV_Server structure.");
	}
	server->ip.host = 0;
	server->ip.port = 0;
	server->home = NULL;
	server->is_on = 0;
	server->max_id_client = 1;

	server->nickname_to_id = MLV_create_tree_map();
	server->id_to_nickname = MLV_create_tree_map();
	server->id_to_socket = MLV_create_tree_map();

	server->mutex = SDL_CreateMutex();

	server->set = SDLNet_AllocSocketSet( max_conection );
	if( !server->set ) {
		PRINT_ERROR( "Unable to allocate a set of sockets." );
	    ERROR( SDLNet_GetError() );
	}
	server->clients = NULL;
	server->nb_client = 0;

	server->port = port;
	server->max_conection = max_conection;
	return server;
}

void free_mlv_server( MLV_Server * server ){
	SDLNet_FreeSocketSet( server->set );
	SDL_DestroyMutex( server->mutex );
	free( server );
}

typedef struct {
	Uint16 nickname_id;
	Uint16 type;
	Uint32 value;
} MLV_Net_header;

MLV_Net_protocol get_message(
	TCPsocket clients, char** message, int* integer, float* real, 
	Uint16* nickname_id
){
	MLV_Net_header data;  // be sure that -fno_anti_aliasing is used with gcc.
	int result = SDLNet_TCP_Recv( clients, &data, sizeof(MLV_Net_header) );
	if( result == 0 ){
		fprintf( stderr, "The connexion was closed !\n" );
		return 1;
	}
	if( result != sizeof(MLV_Net_header) ){
		fprintf( stderr, "Nb reveived : %d \n", result );
		PRINT_ERROR("error when reading a message.");
		return 1;
	}
	*nickname_id = SDLNet_Read16(&data.nickname_id);
	Uint32 value = SDLNet_Read32(&data.value);
	MLV_Net_protocol type = (MLV_Net_protocol) SDLNet_Read16(
		&data.type
	);
	switch( type ){
		case MLV_NET_P_ID_REQUEST:
		case MLV_NET_P_LOGIN_DECLARATION:
		case MLV_NET_P_TEXT:{
				if( message ){
					size_t len = value;
					*message = MLV_MALLOC( value, char );
					int result = SDLNet_TCP_Recv( clients, *message, len );
					if( result != len ){
						PRINT_ERROR("error when reading a message.");
						return 1;
					}
				}
			}
		case MLV_NET_P_NICKNAME_REQUEST:
		case MLV_NET_P_ID_ANSWER:
		case MLV_NET_P_LOGIN_YET_USED:
		case MLV_NET_P_ID_AFFECTATION:
		case MLV_NET_P_SERVER_FULL:
		case MLV_NET_P_INTEGER:
			if( integer ) *integer = value;
			break;
		case MLV_NET_P_REAL:
			if( real ) *real = (float) value;
			break; 
		default:
			ERROR("Invalid value");
	}
	return type;
}

int send_header_hwd(
	TCPsocket socket, Uint16 nickname_id, Uint32 type, Uint32 value
){
	MLV_Net_header data;  // be sure that -fno_anti_aliasing is used with gcc.
	SDLNet_Write16( nickname_id, &(data.nickname_id) );
	SDLNet_Write16( (Uint16) type, &(data.type) );
	SDLNet_Write32( value, &data.value );
	unsigned int t = SDLNet_TCP_Send( socket, &data, sizeof(MLV_Net_header)	);
	return t != sizeof(MLV_Net_header);
}

int send_text_hwd(
	TCPsocket socket, Uint16 nickname_id, MLV_Net_protocol type_msg,
	const char* message
){
	size_t len = strlen( message ) + 1;
	if( len > UINT32_MAX  ){
		PRINT_ERROR( "Message too long ." );
		return 1;
	};
	if( send_header_hwd( socket, nickname_id, type_msg, len ) ){
		PRINT_ERROR("MLV Net : Fail to send the header.");
		return 1;		
	}

	int result = SDLNet_TCP_Send( socket, message, len );
	if( result!=len ){ 
		printf("SDLNet_TCP_Send: %s\n",SDLNet_GetError());
		return 1;
	}
	return 0;
}


const char* request_a_nickname(
	MLV_Server_connection* server_connection, int id
){
	const char * result;
	printf("We request an nickname for : %d.\n", id );
	if( 
		send_header_hwd(
			server_connection->socket, 0, MLV_NET_P_NICKNAME_REQUEST, id
		)
	){
		PRINT_ERROR("MLV_Net protocol : Connexion error.\n");
		assert(0);
	}
	char * nickname;
	Uint16 exp_id;
	MLV_Net_protocol type = get_message(
		server_connection->socket, &nickname, NULL, NULL, &exp_id
	);
	if( type != MLV_NET_P_NICKNAME_ANSWER || exp_id != 0 ){
		PRINT_ERROR("MLV_Net Protocol error.");
		fprintf(stderr, " type : %d, exp_id : %d \n.", type, exp_id );
		assert(0);
	}
	printf("Nickname received : %s.\n", nickname );

	{
		MLV_Key* key = MLV_create_key( strdup(nickname), free, cmp_str );
		int * data = malloc( sizeof(int) );
		*data = id;
		MLV_add_data_in_tree_map(
			key, data, free, server_connection->nickname_to_id
		);
	}

	{
		int * v = malloc( sizeof(int) );
		*v = id;
		MLV_Key* key = MLV_create_key( v, free, cmp_int );
		char * data = strdup( nickname );
		MLV_add_data_in_tree_map(
			key, data, free, server_connection->id_to_nickname
		);
		result = data;
	}
	free(nickname);
	return result;
}


int request_an_id(
	MLV_Server_connection* server_connection,
	const char* nickname
){
	printf("We request an id for : %s.\n", nickname );
	if( 
		send_text_hwd(
			server_connection->socket, 0, MLV_NET_P_ID_REQUEST, nickname
		)
	){
		PRINT_ERROR("MLV_Net protocol : Connexion error.\n");
		assert(0);
	}
	int id;
	Uint16 exp_id;
	MLV_Net_protocol type = get_message(
		server_connection->socket, NULL, &id, NULL, &exp_id
	);
	if( type != MLV_NET_P_ID_ANSWER || exp_id != 0 ){
		PRINT_ERROR("MLV_Net Protocol error.");
		assert(0);
	}
	printf("Id received : %d.\n", id );

	{
		MLV_Key* key = MLV_create_key( strdup(nickname), free, cmp_str );
		int * data = malloc( sizeof(int) );
		*data = id;
		MLV_add_data_in_tree_map(
			key, data, free, server_connection->nickname_to_id
		);
	}

	{
		int * v = malloc( sizeof(int) );
		*v = id;
		MLV_Key* key = MLV_create_key( v, free, cmp_int );
		char * data = strdup( nickname );
		MLV_add_data_in_tree_map(
			key, data, free, server_connection->id_to_nickname
		);
	}

	return id;
}

const char* get_nickname_from_id( MLV_TreeMap* map, int id ){
	const char * resultat;
	int* v = malloc( sizeof(int) );
	*v = id;
	MLV_Key* key = MLV_create_key( v, free, cmp_int );
	MLV_Pair_key_data key_data = MLV_find_tree_map( key, map );
	if( ! key_data.key ){
		resultat = NULL;
	}else{
		resultat = (const char *) (key_data.data);
	}
	MLV_free_key( key );
	return resultat;
}


const char* get_nickname(
	MLV_Server_connection* server_connection, int id
){
	const char * result;
	result = get_nickname_from_id( server_connection->id_to_nickname, id );
	if( ! result ){
		result = request_a_nickname( server_connection, id );
	}
	return result;
}


int get_id_from_nickname( MLV_TreeMap* map, const char* nickname ){
	int resultat;
	MLV_Key* key = MLV_create_key( strdup(nickname), free, cmp_str );
	MLV_Pair_key_data key_data = MLV_find_tree_map( key, map );
	if( ! key_data.key ){
		resultat = -1;
	}else{
		resultat = *( (int*) (key_data.data) );
	}
	MLV_free_key( key );
	return resultat;
}

int get_client_from_id( MLV_TreeMap* map, int id ){
	int resultat;
	int* v = malloc( sizeof(int) );
	*v = id;
	MLV_Key* key = MLV_create_key( v, free, cmp_int );
	MLV_Pair_key_data key_data = MLV_find_tree_map( key, map );
	if( ! key_data.key ){
		resultat = -1;
	}else{
		resultat = *( (int*) (key_data.data) );
	}
	MLV_free_key( key );
	return resultat;
}

int get_nickname_id(
	MLV_Server_connection* server_connection,
	const char* destination_nickname
){
	int result;
	if( ! destination_nickname ) return 0;
	result = get_id_from_nickname(
		server_connection->nickname_to_id, destination_nickname
	);
	if( result < 0 ){
		result = request_an_id( server_connection, destination_nickname );
	}
	return result;
}



int send_header(
	MLV_Server_connection* server_connection, const char* destination_nickname,
	Uint32 type, Uint32 value
){
	return send_header_hwd(
		server_connection->socket, 
		get_nickname_id( server_connection, destination_nickname ),
		type, value
	);
}

char* mlv_protocol__server_is_listening( TCPsocket new_client ){
	int size;
	char* nickname;
	Uint16 dest_nickname_id;
	MLV_Net_protocol type = get_message(
		new_client, &nickname, &size, NULL, &dest_nickname_id
	);
	if( type != MLV_NET_P_LOGIN_DECLARATION ){
		PRINT_ERROR("MLV_NET Protpocol Error : Wrong type of message.");
		fprintf(stderr, "MLV_NET Protpocol Error : message type : %d\n", type);
		assert(0);
	}
	if(	dest_nickname_id != 0 ){
		PRINT_ERROR("MLV_NET Protpocol Error : wrong destination nickname.");
		fprintf(
			stderr, "MLV_NET Protpocol Error : nickname id %d \n", 
			dest_nickname_id
		);
		assert(0);
	}
	return nickname;
}


void mlv_protocol__server_is_full( TCPsocket new_client ){
	if( send_header_hwd( new_client, 0, MLV_NET_P_SERVER_FULL, 0 ) ){
		PRINT_ERROR("MLV_Net error : Connexion problem.");
		return;
	}
}


void add_a_new_client( MLV_Server * server,  TCPsocket new_client ){

	char* nickname = mlv_protocol__server_is_listening( new_client );
	printf("Connexion of %s .\n", nickname );
	

	if( SDL_mutexP( server->mutex ) ){ ERROR("Mutex problem in MLV_Server."); }

	server->nb_client += 1;
	server->clients = realloc(
		server->clients, server->nb_client * sizeof(Net_client) 
	);
	if( !(server->clients) ){ 
		ERROR( "Unable to realloc the list of clients." );
	}
	server->clients[ server->nb_client-1 ].socket = new_client;
	if( SDLNet_TCP_AddSocket( server->set, new_client )==-1 ) {
		fprintf(
			stderr, "Unable to add the socket in the pool : %s", 
			SDLNet_GetError()
		);
	}
	int id_client = server->max_id_client;
	server->max_id_client ++;

	{
		MLV_Key* key = MLV_create_key( nickname, free, cmp_str );
		int * id = malloc( sizeof(int) );
		*id = id_client;
		MLV_add_data_in_tree_map(
			key, id, free, server->nickname_to_id
		);
	}

	{
		int * id = malloc( sizeof(int) );
		*id = id_client;
		MLV_Key* key = MLV_create_key( id, free, cmp_int );
		char * data = strdup( nickname );
		MLV_add_data_in_tree_map(
			key, data, free, server->id_to_nickname
		);
	}

	{
		int * id = malloc( sizeof(int) );
		*id = id_client;
		MLV_Key* key = MLV_create_key( id, free, cmp_int );
		int * id_i = malloc( sizeof(int) );
		*id_i = server->nb_client-1;
		MLV_add_data_in_tree_map(
			key, id_i, free, server->id_to_socket
		);
	}
	
	server->clients[ server->nb_client-1 ].id = id_client;

	if( SDL_mutexV( server->mutex ) ){ ERROR("Mutex problem in MLV_Server."); }
	
	printf("ID of %s : %d.\n", nickname, id_client );
	if( send_header_hwd( new_client, 0, MLV_NET_P_ID_AFFECTATION, id_client ) ){
		PRINT_ERROR("MLV_Net error : Connexion problem.");
		return;
	}

}


void check_for_new_incoming_conexion( MLV_Server* server ){
	if( SDLNet_SocketReady( server->home ) ){
		TCPsocket new_client = SDLNet_TCP_Accept( server->home );

		fprintf( stdout, "New incoming client :" );
		fprint_ip( stdout, SDLNet_TCP_GetPeerAddress( new_client ) );
		fprintf( stdout, "\n" );

		if( ! new_client ){
			// The conection fails. This could be a client problem.
			fprintf(
				stdout, "Unable to open the conection : %s", 
				SDLNet_GetError()
			);
		}

		if( server->nb_client < server->max_conection ){
			add_a_new_client( server,  new_client );
		}else{
			fprintf(stdout, "Server is full and can't accept new client.\n");
			mlv_protocol__server_is_full( new_client );
		}
	}
}

void talk_to_clients( MLV_Server* server ){
	if( SDL_mutexP( server->mutex ) ){
		ERROR("Mutex problem in MLV_Server.");
	}

	// Talk with the clients
	int i;
	for( i = 0; i<server->nb_client; i++ ){
		if( SDLNet_SocketReady( server->clients[i].socket ) ){
			char* message = NULL;
			int integer;
			float real;
			Uint16 destinat_id;
			MLV_Net_protocol type = get_message(
				server->clients[i].socket, &message, &integer, &real, 
				&destinat_id
			);
			switch( type ){
				case MLV_NET_P_ID_REQUEST: {
						printf(
							"We receive an id request from %d.\n",
							server->clients[i].id
						);
						printf("  Login searched : %s\n", message );

						int id = get_id_from_nickname(
							server->nickname_to_id, message
						);
						if( id < 0  ){
							printf("  Login unknown.\n" );
						}else{
							printf("  ID = %d.\n", id );
						}
						if(
							send_header_hwd(
								server->clients[i].socket, 0, 
								MLV_NET_P_ID_ANSWER, id
							)
						){
							PRINT_ERROR("MLV_NET ERROR CONNECTION");
							assert(0);
						}
						printf(
							"We send an id=%d answer to %d.\n", id, 
							server->clients[i].id
						);
					}	
					break;
				case MLV_NET_P_NICKNAME_REQUEST: {
						printf(
							"We receive an nickname request from %d.\n",
							server->clients[i].id
						);
						printf("  ID searched : %d\n", integer );

						const char * nickname = get_nickname_from_id(
							server->id_to_nickname, integer
						);
						if( nickname == 0  ){
							printf("  Id unknown.\n" );
						}else{
							printf("  Nickname = %s.\n", nickname );
						}
						if(
							send_text_hwd(
								server->clients[i].socket, 0, 
								MLV_NET_P_NICKNAME_ANSWER, nickname
							)
						){
							PRINT_ERROR("MLV_NET ERROR CONNECTION");
							assert(0);
						}
						printf(
							"We send an nickname=%s answer to %d.\n", nickname, 
							server->clients[i].id
						);
					}	
					break;
				case MLV_NET_P_TEXT: {
						printf(
							"We forward a message from %d to %d.\n",
							server->clients[i].id, destinat_id
						);
						
						printf("    message : %s.\n", message);

						int dest = get_client_from_id( 
							server->id_to_socket, destinat_id
						);
						if( dest<1 ){
							PRINT_ERROR("Le client n'existe pas !");
							assert(0);
						}
						if( send_text_hwd(
							server->clients[dest].socket, server->clients[i].id,
							MLV_NET_P_TEXT, message
						) ){
							PRINT_ERROR("MLV_NET : Connexion problem !");
						}
						printf("    the message is forwarded.\n");
						free(message);
					}
					break;
				default:
					free(message);
			}
		}
	}

	if( SDL_mutexV( server->mutex ) ){
		ERROR("Mutex problem in MLV_Server.");
	}
}

int run( void* data ){
	return 0;
}

MLV_Server* initialize_the_server(unsigned int port, int max_conection){
	MLV_Server* server = allocate_mlv_server( port, max_conection );

	// We prepare IP adress
	if( SDLNet_ResolveHost( &server->ip, NULL, port )==-1 ) {
		fprintf(
			stderr, "Unable to initialise the SDL_Net ip structure : %s", 
			SDLNet_GetError()
		);
		free_mlv_server( server );
		return NULL;
	}

	// We open a listening socket
	server->home = SDLNet_TCP_Open(&server->ip);
	if( !(server->home) ) {
		fprintf(
			stderr, "Unable to open a listening socket for the server : %s", 
			SDLNet_GetError()
		);
		free_mlv_server( server );
		return NULL;
	}

	// We add the server socket into the main socket pool.
	if( SDLNet_TCP_AddSocket( server->set, server->home )==-1 ) {
		fprintf(
			stderr, "Unable to add the socket in the pool : %s", 
			SDLNet_GetError()
		);
		free_mlv_server( server );
		return NULL;
	}

	return server;
}

MLV_Server* MLV_start_server(
	unsigned int port, int max_conection, int (*fct)(void*), void* data
){
	SDL_Thread * thread = NULL;
	MLV_Server* server = initialize_the_server( port, max_conection);

	if( !server ) return NULL;

	server->is_on = 1;

	if( fct ){
		thread = SDL_CreateThread( fct, data );
		if( !thread ){
			PRINT_ERROR( "Unable to start a thread for the server." );
			free_mlv_server( server );
			return NULL;
		}
	}

	fprintf( stdout, "Server is on. \n" );
	while( server->is_on ){
		int numready = SDLNet_CheckSockets(server->set, 0);
		if( numready == -1 ){
			PRINT_ERROR( "Unable to check sockets." );
			ERROR( SDLNet_GetError() );
		}else if( numready ){
			check_for_new_incoming_conexion( server );
			talk_to_clients( server );
		}
		MLV_wait_milliseconds(500);
	}

	if( thread ){
		SDL_WaitThread( thread, NULL );	
	}
	return 0;
}

void MLV_free_server( MLV_Server* server ){
	SDLNet_FreeSocketSet(server->set);
	server->set = NULL;
	MLV_FREE( server, MLV_Server );
}

unsigned int MLV_get_port_of_server( MLV_Server* server ){
	return server->port;
}





MLV_Network_data_type MLV_get_network_data(
	MLV_Server_connection* connection, 
	char** message, int* integer, float* real, char const ** nickname
){
	MLV_Network_data_type result = MLV_NET_NONE;
	int numready = SDLNet_CheckSockets(connection->set, 0);
	if( numready == -1 ){
		PRINT_ERROR( "Unable to check sockets." );
		ERROR( SDLNet_GetError() );
	}else if( numready ){
		DEBUG("Activity !")
		Uint16 nickname_id;
		result = get_message(
			connection->socket, message, integer, real, &nickname_id
		);
		*nickname = get_nickname( connection, nickname_id );
	}
	return result;
}


void init_server_connection( MLV_Server_connection * conection ){
	conection->ip.host = 0;
	conection->ip.port = 0;
	conection->socket = NULL;
	conection->set = NULL;
	conection->nickname_id = 0;
	conection->nickname = NULL;
	conection->nickname_to_id = MLV_create_tree_map();
	conection->id_to_nickname = MLV_create_tree_map();
}


MLV_Server_connection* MLV_connect_to_server(
	const char* server_address, unsigned int port,  const char* nickname
){
	MLV_Server_connection* conection = MLV_MALLOC( 1, MLV_Server_connection );
	init_server_connection( conection );

	conection->set = SDLNet_AllocSocketSet( 1 );
	if( !conection->set ) {
		PRINT_ERROR( "Unable to allocate a set of sockets." );
	    ERROR( SDLNet_GetError() );
	}

	/* Resolve the argument into an IPaddress type */
	if(SDLNet_ResolveHost( &(conection->ip), server_address, port )==-1){
		PRINT_ERROR( SDLNet_GetError() );
		ERROR( "Unable to resolve the web address." );
	}

	/* open the server socket */
	conection->socket= SDLNet_TCP_Open( &(conection->ip) );
	if( ! conection->socket ){
		PRINT_ERROR( SDLNet_GetError() );
		ERROR("Unable to open the TCP socket." );
	}

	fprintf( stdout, "Connection to :" );
	fprint_ip( stdout, SDLNet_TCP_GetPeerAddress( conection->socket ) );
	fprintf( stdout, "\n" );

	if( SDLNet_TCP_AddSocket( conection->set, conection->socket )==-1 ) {
		fprintf(
			stderr, "Unable to add the socket in the pool : %s", 
			SDLNet_GetError()
		);
	}

	fprintf( stdout, "We send our login: %s.\n", nickname );
	if( send_text_hwd(
		conection->socket, 0, MLV_NET_P_LOGIN_DECLARATION, nickname
	) ){
		PRINT_ERROR("MLV_NET : Connexion problem !");
	}

	int id;
	Uint16 exp_id;
	MLV_Net_protocol type = get_message(
		conection->socket, NULL, &id, NULL, &exp_id
	);
	switch( type ){
		case MLV_NET_P_ID_AFFECTATION: {
				if( ! exp_id ){
					fprintf( 
						stdout, 
						"Connection is established. Our id is : %d.\n", id
					);
				}else{
					PRINT_ERROR("MLV_Net protocol : Invalid packet.");
					assert(0);
				}
				conection->nickname_id = id;
				conection->nickname = strdup( nickname );
				{
					MLV_Key* server_key = MLV_create_key(
						strdup(nickname), free, cmp_str
					);
					int * data = malloc( sizeof(int) );
					*data = id;
					MLV_add_data_in_tree_map(
						server_key, data, free, conection->nickname_to_id
					);
				}
				{
					int * v = malloc( sizeof(int) );
					*v = id;
					MLV_Key* key = MLV_create_key( v, free, cmp_int );
					char * data = strdup( nickname );
					MLV_add_data_in_tree_map(
						key, data, free, conection->id_to_nickname
					);
				}
			}
			break;
		case MLV_NET_P_SERVER_FULL:
			fprintf( stdout, "Server is full.\n" );
			assert(0);
		case MLV_NET_P_LOGIN_YET_USED: 
			fprintf( stdout, "Login is yet used.\n" );
			assert(0);
		default :
			fprintf( 
				stderr, 
				"MLV_Net protocol : Invalid packet or connection is lost."
			);
			assert(0);
	}
	return conection;
}

void MLV_disconect( MLV_Server_connection* conection ){
	TODO
}

int MLV_get_conected_computers(
	MLV_Server_connection* server_connection, char** const * array_of_nicknames
){
	TODO
	return 0;
}

int MLV_send_message_to_network(
	MLV_Server_connection* server_connection, const char* destination_nickname, 
	const char* message
){
	return send_text_hwd(
		server_connection->socket, 
		get_nickname_id( server_connection, destination_nickname ),
		MLV_NET_P_TEXT, message
	);
}


int MLV_send_integer_to_network(
	MLV_Server_connection* server_connection,
	const char* destination_nickname, int integer
){
	return send_header(
		server_connection, destination_nickname, MLV_NET_INTEGER, integer
	);
}

int MLV_send_real_to_network(
	MLV_Server_connection* server_connection, 
	const char* destination_nickname, float real
){
	return send_header(
		server_connection, destination_nickname, MLV_NET_REAL, (Uint32) real
	);
}

int MLV_send_message_over_network_to_everybody(
	MLV_Server_connection* server_connection, const char* message
){
	return MLV_send_message_to_network( server_connection, NULL, message );
}

int MLV_send_integer_over_network_to_everybody(
	MLV_Server_connection* server_connection, int integer
){
	return MLV_send_integer_to_network( server_connection, NULL, integer );
}

int MLV_send_real_over_network_to_everybody(
	MLV_Server_connection* server_connection, float real
){
	return MLV_send_real_to_network( server_connection, NULL, real );
}

