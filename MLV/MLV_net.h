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

/** \~french 
 * \file MLV_net.h
 *
 * \author Adrien Boussicault
 * \author Marc Zipstein
 *
 * \brief Ce fichier définit les prototypes des fonctions permettant de faire
 *        comuniquer différents ordinateurs par un réseau.
 */

#ifndef __MLV__MLV_NET_H__
#define __MLV__MLV_NET_H__

#ifdef __cplusplus
extern "C" {
#endif


#if 0
typedef struct _MLV_Net MLV_Net;

MLV_Net* MLV_create_network_conection( const* ip );
MLV_Net* MLV_create_advanced_network_conection( const* ip, unsigned int port );

void MLV_send_message( MLV_Net* );

MLV_free_network_conection( MLV_Net );
#endif

int MLV_init_network();
void MLV_free_network();

typedef struct _MLV_Server MLV_Server;


MLV_Server* MLV_start_server(
	unsigned int port, int max_conection, int (*fct)(void*), void* data
);
void MLV_free_server();
unsigned int MLV_get_port_of_server( MLV_Server* );


typedef struct _MLV_Server_connection MLV_Server_connection;

int MLV_get_network_message( char* nickname, char* text );

MLV_Server_connection* MLV_connect_to_server( 
	const char* server_address, unsigned int port,  const char* nickname
);
int MLV_connection_is_up( MLV_Server_connection* connection );

void MLV_disconect( MLV_Server_connection* conection );
int MLV_get_conected_computers(
	MLV_Server_connection* server_conection, char** const * array_of_nicknames
);

int MLV_send_message_to_network(
	MLV_Server_connection*, const char* destination_nickname, 
	const char* message
);
int MLV_send_integer_to_network(
	MLV_Server_connection* server_connection,
	const char* destination_nickname, int integer
);
int MLV_send_real_to_network(
	MLV_Server_connection* server_connection,
	const char* destination_nickname, float real
);

int MLV_send_message_over_network_to_everybody(
	MLV_Server_connection* server_connection, const char* message
);
int MLV_send_integer_over_network_to_everybody(
	MLV_Server_connection* server_connection, int integer
);
int MLV_send_real_over_network_to_everybody(
	MLV_Server_connection* server_connection, float real
);


typedef enum {
	MLV_NET_NONE = 0, /**< \~french Aucune donnée récupérée */
	MLV_NET_TEXT = 1, /**< \~french La donnée récupérée est du texte.*/
	MLV_NET_INTEGER = 2, /**< \~french La donnée récupérée est un entier. */
	MLV_NET_REAL = 3 /**< \~french  La donnée récupérée est un réel. */
} MLV_Network_data_type;

MLV_Network_data_type MLV_get_network_data(
	MLV_Server_connection* connection,
	char** message, int* integer, float* real, char const ** nickname
);

#ifdef __cplusplus
}
#endif

#endif
