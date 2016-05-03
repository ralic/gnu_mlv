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

/** \~french 
 * \file MLV_net.h
 *
 * \author Adrien Boussicault
 *
 * \brief Ce fichier définit les prototypes des fonctions permettant de faire
 *        comuniquer différents ordinateurs par un réseau.
 */

#ifndef __MLV__MLV_NET_H__
#define __MLV__MLV_NET_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	MLV_NET_NONE = 0, /**< \~french Aucune donnée récupérée */
	MLV_NET_TEXT = 1, /**< \~french La donnée récupérée est du texte.*/
	MLV_NET_INTEGER = 2, /**< \~french La donnée récupérée est un entier. */
	MLV_NET_REAL = 3, /**< \~french  La donnée récupérée est un réel. */

	MLV_NET_SERVER_IS_FULL = -1,
	MLV_NET_CONEXION_REFUSED = -2, 
	MLV_NET_CONEXION_DROPED = -3 
} MLV_Network_msg;

int MLV_init_network();
void MLV_free_network();

typedef struct _MLV_Server MLV_Server;

MLV_Server* MLV_start_server( unsigned int port, int max_conexion );
void MLV_free_server();

unsigned int MLV_get_port_of_server( MLV_Server* );
void MLV_collect_conexion_informations(
	MLV_Conexion* conexion, const char * ip, int port,   
);

MLV_Conexion * MLV_get_new_conexion( MLV_Server serve* server );

void MLV_accept_conexion( MLV_Conexion* conexion );
void MLV_refuse_conexion( MLV_Conexion* conexion );

MLV_Conexion * MLV_start_new_conexion( 
	const char* server_address, unsigned int port
);

MLV_free_conexion( MLV_Conexion* conexion );

MLV_Network_msg MLV_send_text(
	MLV_Conexion* conexion, const char* text, int size
);
MLV_Network_msg MLV_send_integer_array(
	MLV_Conexion* conexion, int * array, int size
);
MLV_Network_msg MLV_send_real_array(
	MLV_Conexion* conexion, float* array, int size
);

MLV_Network_msg MLV_get_network_data(
	MLV_Connection* connection, char** message, int** integers, float** reals,
	int* size
);

#ifdef __cplusplus
}
#endif

#endif
