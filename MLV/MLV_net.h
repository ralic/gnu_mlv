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


MLV_Server* MLV_start_server( unsigned int port, int max_conection );
void MLV_free_server();
unsigned int MLV_get_port_of_server( MLV_Server* );


typedef struct _MLV_Server_conection MLV_Server_conection;

MLV_Server_conection* MLV_conect_to_server( 
	const char* server_address, unsigned int port,  const char* nickname 
);
void MLV_disconect( MLV_Server_conection* conection );
int MLV_get_conected_computers(
	MLV_Server_conection* server_conection, char** const * array_of_nicknames
);
int MLV_send_message(
	MLV_Server_conection*, const char* destination_nickname, 
	const char* message
);
int MLV_send_message_to_everybody(
	MLV_Server_conection*, const char* message
);


#ifdef __cplusplus
}
#endif

#endif
