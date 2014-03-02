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

#include "data_structure.h"

#include "platform.h"

#if defined( OS_WINDOWS )
#	include <SDL/SDL_net.h>
#elif defined( OS_APPLE )
#	include <SDL_net/SDL_net.h>
#else
#	include <SDL/SDL_net.h>
#endif

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

struct _MLV_Server {
	IPaddress ip;
	TCPsocket home;

	int max_conection;
	int port;

	SDLNet_SocketSet set;
	TCPsocket* clients;	
	size_t nb_client;
};

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


MLV_Server * allocate_mlv_server( unsigned int port, int max_conection ){
	MLV_Server* server = MLV_MALLOC( 1, MLV_Server );
	if( !server ){
		ERROR("Unable to allocate MLV_Server structure.");
	}
	server->ip.host = 0;
	server->ip.port = 0;
	server->home = NULL;

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
	free( server );
}


void mlv_protocol__server_is_listening( TCPsocket new_client ){
	unsigned char data = 0;
	SDLNet_TCP_Send( new_client, &data, 1 );
}


void mlv_protocol__server_is_full( TCPsocket new_client ){
	unsigned char data = 1;
	SDLNet_TCP_Send( new_client, &data, 1 );
}



MLV_Server* MLV_start_server( unsigned int port, int max_conection ){
	
	MLV_Server* server = allocate_mlv_server( port, max_conection );

	// We prepare IP adress
	if( SDLNet_ResolveHost( &server->ip, NULL, port )==-1 ) {
		PRINT_ERROR( "Unable to initialise the SDL_Net ip structure." );
		ERROR( SDLNet_GetError() );
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

	fprintf( stdout, "Server is on. \n" );

	// We add the server socket into the main socket pool.
	if( SDLNet_TCP_AddSocket( server->set, server->home )==-1 ) {
		PRINT_ERROR( "Unable to add the socket in the pool" );
		ERROR( SDLNet_GetError() );
	}

	TCPsocket new_client;

	while(1){
		int numready = SDLNet_CheckSockets(server->set, 0);
		if( numready == -1 ){
			PRINT_ERROR( "Unable to check sockets." );
			ERROR( SDLNet_GetError() );
		}else if( numready ){
			// Check if there are new client
			if( SDLNet_SocketReady( server->home ) ) {
				new_client = SDLNet_TCP_Accept( server->home );
				if( new_client ){
					
					fprintf( stdout, "New incoming client :" );
					fprint_ip( stdout, SDLNet_TCP_GetPeerAddress( new_client ) );
					fprintf( stdout, "\n" );

					if( server->nb_client < server->max_conection ){
						server->nb_client += 1;
						server->clients = realloc(
							server->clients, server->nb_client
						);
						if( !(server->clients) ){
							ERROR( "Unable to realloc the list of clients." );
						}
						server->clients[ server->nb_client-1 ] = new_client;
						
						mlv_protocol__server_is_listening( new_client );
					}else{
						fprintf(stdout, "Server is full and can't accept new client.\n");
						mlv_protocol__server_is_full( new_client );
					}
				}else{
					// The conection fails. This could be a client problem.
					fprintf(
						stdout, "Unable to open the conection : %s", 
						SDLNet_GetError()
					);
				}
			}
			// Talk with the clients
			int i;
			for( i = 0; i<server->nb_client; i++ ){
				
			}
		}
	}
	
	SDLNet_TCP_AddSocket(server->set,server);
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



struct _MLV_Server_conection {
	IPaddress ip;
	TCPsocket socket;

};

void init_server_conection( MLV_Server_conection * conection ){
	conection->ip.host = 0;
	conection->ip.port = 0;
	conection->socket = NULL;
}


MLV_Server_conection* MLV_conect_to_server(
	const char* server_address, unsigned int port,  const char* nickname
){
	MLV_Server_conection* conection = MLV_MALLOC( 1, MLV_Server_conection );
	init_server_conection( conection );

	/* Resolve the argument into an IPaddress type */
	if(SDLNet_ResolveHost( &(conection->ip), server_address, port )==-1)
	{
		PRINT_ERROR( SDLNet_GetError() );
		ERROR( "Unable to resolve the web address." );
	}

	/* open the server socket */
	conection->socket= SDLNet_TCP_Open( &(conection->ip) );
	if( ! conection->socket )
	{
		PRINT_ERROR( SDLNet_GetError() );
		ERROR("Unable to open the TCP socket." );
	}

	fprintf( stdout, "Connection to :" );
	fprint_ip( stdout, SDLNet_TCP_GetPeerAddress( conection->socket ) );
	fprintf( stdout, "\n" );

	unsigned char data = 0;
	int result = SDLNet_TCP_Recv( conection->socket, &data, 1 );
	if( result ){
		if( data ){
			fprintf( stdout, "Server is full.\n" );	
		}else{
			fprintf( stdout, "Server is listening.\n" );	
			const char* msg = "Cocucou";
			int len = strlen( msg ) + 1;
			int result=SDLNet_TCP_Send(conection->socket,msg,len);
			if(result<len){ 
				printf("SDLNet_TCP_Send: %s\n",SDLNet_GetError());
			}
		}
	}else{
		fprintf( stdout, "The connection is lost.\n" );	
	}


	return conection;
}


void MLV_disconect( MLV_Server_conection* conection ){
	TODO
}

int MLV_get_conected_computers(
	MLV_Server_conection* server_conection, char** const * array_of_nicknames
){
	TODO
	return 0;
}

int MLV_send_message(
	MLV_Server_conection* server_conection, const char* destination_nickname, 
	const char* message
){
	TODO
	return 0;
}

int MLV_send_message_to_everybody(
	MLV_Server_conection* server_conection, const char* message
){
	TODO
	return 0;
}

