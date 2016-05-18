/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2016 Adrien Boussicault
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

#include "data_structure.h"

#include "platform.h"
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

typedef struct _Human_ip {
	char* host;
	unsigned int ip[4];
	unsigned int port;
} Human_ip;

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


struct _MLV_Connection {
	IPaddress ip;
	TCPsocket socket;

	SDLNet_SocketSet set;
	int client;
};

MLV_Connection* create_empty_connextion(){
	MLV_Connection* connection = MLV_MALLOC( 1, MLV_Connection );
	connection->ip.host = 0;
	connection->ip.port = 0;
	connection->socket = NULL;
	connection->set = NULL;
	connection->client = 0;
	return connection;
}

typedef struct {
	TCPsocket socket;
} Net_client;

struct _MLV_Server {
	int max_connections;
	int port;

	int nb_client;
	IPaddress ip;
	TCPsocket incoming_observer;
	SDLNet_SocketSet incoming_observer_set;
	SDLNet_SocketSet connection_set;
};






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

MLV_Server * allocate_mlv_server( unsigned int port, int max_connections ){
	MLV_Server* server = MLV_MALLOC( 1, MLV_Server );
	if( !server ){
		ERROR("Unable to allocate MLV_Server structure.");
		exit(1);
	}
	server->ip.host = 0;
	server->ip.port = 0;
	server->incoming_observer = NULL;
	server->nb_client = 0;

//	server->mutex = SDL_CreateMutex();

	server->incoming_observer_set = SDLNet_AllocSocketSet( 1 );
	if( !server->incoming_observer_set ) {
		ERROR( "Unable to allocate the incoming observer." );
	    ERROR( SDLNet_GetError() );
		exit(1);
	}

	server->connection_set = SDLNet_AllocSocketSet( max_connections );
	if( !server->connection_set ) {
		ERROR( "Unable to allocate a the set of connection sockets." );
	    ERROR( SDLNet_GetError() );
		exit(1);
	}

	server->port = port;
	server->max_connections = max_connections;
	return server;
}

void free_mlv_server( MLV_Server * server ){
	SDLNet_FreeSocketSet( server->incoming_observer_set );
	SDLNet_FreeSocketSet( server->connection_set );
//	SDL_DestroyMutex( server->mutex );

	free( server );
}

MLV_Server* MLV_start_server( unsigned int port, int max_connections ){
	MLV_Server* server = allocate_mlv_server( port, max_connections );

	// We prepare IP adress
	if( SDLNet_ResolveHost( &server->ip, NULL, port )==-1 ) {
		fprintf(
			stderr, "Unable to initialise the SDL_Net ip structure : %s", 
			SDLNet_GetError()
		);
		exit(1);
		free_mlv_server( server );
		return NULL;
	}

	// We open a listening socket
	server->incoming_observer = SDLNet_TCP_Open(&server->ip);
	if( !(server->incoming_observer) ) {
		fprintf(
			stderr, "Unable to open a listening socket for the server : %s", 
			SDLNet_GetError()
		);
		free_mlv_server( server );
		return NULL;
	}

	// We add the server socket into the main socket pool.
	if( 
		SDLNet_TCP_AddSocket( 
				server->incoming_observer_set, server->incoming_observer 
		)==-1 
	) {
		fprintf(
			stderr, "Unable to add the socket in the pool : %s", 
			SDLNet_GetError()
		);
		free_mlv_server( server );
		return NULL;
	}

	return server;
}

void MLV_free_server(MLV_Server* server ){
	free_mlv_server( server );
}

unsigned int MLV_get_port_of_server( MLV_Server* server ){
	return server->port;
}

void MLV_collect_server_informations(
	MLV_Server* server, const char ** ip, int * port
){
	TODO
}

typedef struct {
	Uint16 type;
	Uint32 value;
} MLV_Net_header;

int send_header_hwd(
	TCPsocket socket, Uint32 type, Uint32 value
){
	MLV_Net_header data;  // be sure that -fno_anti_aliasing is used with gcc.
	SDLNet_Write16( (Uint16) type, &(data.type) );
	SDLNet_Write32( value, &data.value );
	unsigned int t = SDLNet_TCP_Send( socket, &data, sizeof(MLV_Net_header)	);
	return t != sizeof(MLV_Net_header);
}


void mlv_protocol__server_is_full( TCPsocket new_client ){
	if( send_header_hwd( new_client, MLV_NET_SERVER_IS_FULL, 0 ) ){
		ERROR("MLV_Net error : Connexion problem.");
		return;
	}
}



MLV_Connection* add_a_new_client(
	MLV_Server * server,  TCPsocket new_client
){
	MLV_Connection* connection = create_empty_connextion();

	IPaddress* ip=SDLNet_TCP_GetPeerAddress(new_client);
	connection->socket = new_client;
	connection->client = 0;
	connection->ip = *ip;

	if( SDLNet_TCP_AddSocket( server->connection_set, new_client )==-1 ) {
		fprintf(
			stderr, "Unable to add the socket in the pool : %s", 
			SDLNet_GetError()
		);
	}

	if( send_header_hwd( new_client, MLV_NET_CONNECTION_ACCEPTED, 0 ) ){
		fprintf(stderr, "MLV_Net error : Connexion problem.");
		return 0;
	}
	server->nb_client++;
	return connection;
}


MLV_Connection * get_new_connection( MLV_Server* server ){
	MLV_Connection* result = NULL;
	if( SDLNet_SocketReady( server->incoming_observer ) ){
		TCPsocket new_client = SDLNet_TCP_Accept( server->incoming_observer );

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

		if( server->nb_client < server->max_connections ){
			result = add_a_new_client( server,  new_client );
		}else{
			fprintf(stdout, "Server is full and can't accept new client.\n");
			mlv_protocol__server_is_full( new_client );
		}
	}
	return result;
}


MLV_Connection * MLV_get_new_connection( MLV_Server* server ){
	MLV_Connection * result = NULL;
	int numready = SDLNet_CheckSockets(server->incoming_observer_set, 0);
	if( numready == -1 ){
		fprintf( stderr, "Unable to check incoming socket." );
		ERROR( SDLNet_GetError() );
	}else if( numready ){
		result = get_new_connection( server );
	}
	return result;
}

void MLV_collect_connection_informations(
	MLV_Connection* server, const char ** ip, int* port
){
	TODO
}

void MLV_accept_connection( MLV_Connection* connection ){
	TODO
}

void MLV_refuse_connection( MLV_Connection* connection ){
	TODO
}

MLV_Network_msg get_fixed_array_message(
	TCPsocket clients, 
	char* message, int* integers, float* reals, int size
){
	MLV_Net_header data;  // be sure that -fno_anti_aliasing is used with gcc.
	int result = SDLNet_TCP_Recv( clients, &data, sizeof(MLV_Net_header) );
	if( result == 0 ){
		fprintf( stderr, "The connexion was closed !\n" );
		return MLV_NET_CONNECTION_CLOSED;
	}
	if( result != sizeof(MLV_Net_header) ){
		fprintf( stderr, "Nb reveived : %d \n", result );
		ERROR("error when reading a message.");
	}
	Uint32 value = SDLNet_Read32(&data.value);
	MLV_Network_msg type = (MLV_Network_msg) SDLNet_Read16( &data.type );

	switch( type ){
		case MLV_NET_TEXT: ; 
		case MLV_NET_INTEGERS: ;
		case MLV_NET_REALS: ;
			if( size && size != value ){
				fprintf( stderr,
					"Invalid parameter. The size of the data is %d. "
					"Excpected data is : %d.\n",
					value, size
				);
				exit(1);
			} 
			break; 
		default: ;
	}

	switch( type ){
		case MLV_NET_TEXT: if( message ){
				int result = SDLNet_TCP_Recv( clients, message, size );
				if( result != size ){
					ERROR( "error when reading a message." );
				}
			}
			
		case MLV_NET_INTEGERS: if( integers ){
				Uint32 values[size];
				int result = SDLNet_TCP_Recv(
					clients, values, sizeof(values)
				);
				if( result != sizeof(values) ){
					ERROR( "error when reading a message." );
				}
				for( int i=0; i<size; i++ ){
					integers[i] = SDLNet_Read32( values[i] );
				}
			}
		case MLV_NET_CONNECTION_ACCEPTED:; 
		case MLV_NET_SERVER_IS_FULL:;
		case MLV_NET_CONNECTION_REFUSED:;
		case MLV_NET_CONNECTION_CLOSED:;
			if( integers ) *integers = value;
			break;
		case MLV_NET_REALS:
			TODO
			break; 
		default:
			ERROR("MLV NET: Unexpectd value.");
	}
	return type;
}




MLV_Network_msg get_message(
	TCPsocket clients, char** message, int** integers, float** reals, int* size
){
	MLV_Net_header data;  // be sure that -fno_anti_aliasing is used with gcc.
	int result = SDLNet_TCP_Recv( clients, &data, sizeof(MLV_Net_header) );
	if( result == 0 ){
		fprintf( stderr, "The connexion was closed !\n" );
		return MLV_NET_CONNECTION_CLOSED;
	}
	if( result != sizeof(MLV_Net_header) ){
		fprintf( stderr, "Nb reveived : %d \n", result );
		ERROR("error when reading a message.");
	}
	Uint32 value = SDLNet_Read32(&data.value);
	MLV_Network_msg type = (MLV_Network_msg) SDLNet_Read16( &data.type );
	switch( type ){
		case MLV_NET_TEXT:{
				size_t len = value;
				if( message ){
					*message = MLV_MALLOC( value, char );
					int result = SDLNet_TCP_Recv( clients, *message, len );
					if( result != len ){
						ERROR( "error when reading a message." );
					}
				}
				if( size ){
					*size = len;
				}
			}
		case MLV_NET_INTEGERS:;
		case MLV_NET_REALS:
			TODO
			break; 
		default:
			ERROR("Invalid value");
	}
	return type;
}


MLV_Connection * MLV_start_new_connection( 
	const char* server_address, unsigned int port
){
	MLV_Connection* connection = create_empty_connextion();

	connection->set = SDLNet_AllocSocketSet( 1 );
	if( !connection->set ) {
		fprintf( stderr, "Unable to allocate a set of sockets." );
	    ERROR( SDLNet_GetError() );
	}

	/* Resolve the argument into an IPaddress type */
	if(SDLNet_ResolveHost( &(connection->ip), server_address, port )==-1){
		fprintf( stderr, "%s\n", SDLNet_GetError() );
		fprintf( stderr, "Unable to resolve the web address.\n" );
		MLV_free_connection( connection );
		return 0;
	}

	/* open the server socket */
	connection->socket= SDLNet_TCP_Open( &(connection->ip) );
	if( ! connection->socket ){
		fprintf( stderr, "%s\n", SDLNet_GetError() );
		fprintf( stderr, "Unable to open the TCP socket.\n" );
		MLV_free_connection( connection );
		return 0;
	}

	fprintf( stdout, "Connection to :" );
	fprint_ip( stdout, SDLNet_TCP_GetPeerAddress( connection->socket ) );
	fprintf( stdout, "\n" );

	if( SDLNet_TCP_AddSocket( connection->set, connection->socket )==-1 ) {
		fprintf(
			stderr, "%s", 
			SDLNet_GetError()
		);
	    ERROR( "Unable to add the socket in the pool" );
	}

	int value;

	MLV_Network_msg type = get_fixed_array_message(
		connection->socket, NULL, &value, NULL, 0
	);
	switch( type ){
		case  MLV_NET_CONNECTION_ACCEPTED: {
				fprintf( stdout, "Connection is established.\n" );
			}
			break;
		case MLV_NET_SERVER_IS_FULL:
			fprintf( stdout, "Server is full.\n" );
			MLV_free_connection( connection );
			connection = NULL;
			break;
		case MLV_NET_CONNECTION_REFUSED: 
			fprintf( stdout, "Connection was refused.\n" );
			MLV_free_connection( connection );
			connection = NULL;
			break;
		case MLV_NET_CONNECTION_CLOSED: 
			fprintf( stdout, "Connection was closed.\n" );
			MLV_free_connection( connection );
			connection = NULL;
			break;
		default :
			ERROR( 
				"MLV_Net protocol : Invalid packet."
			);
	}
	return connection;
}

void MLV_free_connection( MLV_Connection* connection ){
	if( connection->socket ){
		SDLNet_TCP_DelSocket(connection->set, connection->socket);
		SDLNet_TCP_Close(connection->socket);
	}
	if( connection->set ){
		SDLNet_FreeSocketSet(connection->set);
	}
	MLV_FREE( connection, MLV_Connection );
}

MLV_Network_msg send_text_hwd(
	TCPsocket socket, MLV_Network_msg type_msg, const char* message
){
	size_t len = strlen( message ) + 1;
	if( len > UINT32_MAX  ){
		fprintf( 
			stderr, "Message too long. We keep just %d characters.",
			UINT32_MAX - 1
		);
		len = UINT32_MAX;
	};
	if( send_header_hwd( socket, type_msg, len ) ){
		fprintf( stderr, "MLV Net : Fail to send the header.");
		return MLV_NET_CONNECTION_CLOSED;
	}

	int result = SDLNet_TCP_Send( socket, message, len );
	if( result!=len ){ 
		fprintf( stderr, "SDLNet_TCP_Send: %s\n",SDLNet_GetError());
		return MLV_NET_CONNECTION_CLOSED;
	}
	return type_msg;
}

MLV_Network_msg MLV_send_text(
	MLV_Connection* connection, const char* text, int size
){
	return send_text_hwd( connection->socket, MLV_NET_TEXT, text );
}


MLV_Network_msg send_integers_hwd(
	TCPsocket socket, MLV_Network_msg type_msg, const int* integers,
	int size
){
	size_t len = size;
	if( size > UINT32_MAX  ){
		fprintf( 
			stderr, "Message too long. We keep just %d characters.",
			UINT32_MAX - 1
		);
		len = UINT32_MAX;
	};
	if( send_header_hwd( socket, type_msg, len ) ){
		fprintf( stderr, "MLV Net : Fail to send the header.");
		return MLV_NET_CONNECTION_CLOSED;
	}

	Uint32 data[len];
	for( int i=0; i<len; i++ ){
		data[i] = integers[i];
	}
	int result = SDLNet_TCP_Send( socket, data, sizeof(data) );
	if( result!=sizeof(data) ){ 
		fprintf( stderr, "SDLNet_TCP_Send: %s\n",SDLNet_GetError());
		return MLV_NET_CONNECTION_CLOSED;
	}
	return type_msg;
}


MLV_Network_msg MLV_send_integer_array(
	MLV_Connection* connection, const int* array, int size
){
	return send_integers_hwd( 
		connection->socket, MLV_NET_INTEGERS, array, size
	);
}


MLV_Network_msg send_reals_hwd(
	TCPsocket socket, MLV_Network_msg type_msg, const float* reals,
	int size
){
	size_t len = size;
	if( size > UINT32_MAX  ){
		fprintf( 
			stderr, "Message too long. We keep just %d characters.",
			UINT32_MAX - 1
		);
		len = UINT32_MAX;
	};
	if( send_header_hwd( socket, type_msg, len ) ){
		fprintf( stderr, "MLV Net : Fail to send the header.");
		return MLV_NET_CONNECTION_CLOSED;
	}

	Uint32 data[len];
	for( int i=0; i<len; i++ ){
		data[i] = (Uint32) reals[i];
	}
	int result = SDLNet_TCP_Send( socket, data, sizeof(data) );
	if( result!=sizeof(data) ){ 
		fprintf( stderr, "SDLNet_TCP_Send: %s\n",SDLNet_GetError());
		return MLV_NET_CONNECTION_CLOSED;
	}
	return type_msg;
}


MLV_Network_msg MLV_send_real_array(
	MLV_Connection* connection, const float* array, int size
){
	return send_reals_hwd( 
		connection->socket, MLV_NET_REALS, array, size
	);
}

MLV_Network_msg MLV_get_network_data(
	MLV_Connection* connection, char** message, int** integers, 
	float** reals, int* size
){

	MLV_Network_msg result = MLV_NET_NONE;
	int numready = SDLNet_CheckSockets(connection->set, 0);
	if( numready == -1 ){
		fprintf( stderr, "Net problem : %s \n", SDLNet_GetError() );
		ERROR( "Unable to check sockets." );
	}else if( numready ){
		DEBUG("Activity !")
		result = get_message(
			connection->socket, message, integers, reals, size
		);
	}
	return result;
}

