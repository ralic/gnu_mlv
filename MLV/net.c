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

struct _MLV_Server {
};

MLV_Server* MLV_start_server( unsigned int port, int max_connection ){
	TODO
	return NULL;
}
void MLV_free_server(){
	TODO
}

unsigned int MLV_get_port_of_server( MLV_Server* server ){
	TODO
	return 0;
}

void MLV_collect_server_informations(
	MLV_Server* server, const char ** ip, int * port
){
	TODO
}

struct _MLV_Connection {
};

MLV_Connection * MLV_get_new_connection( MLV_Server* server ){
	TODO
	return 0;
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

MLV_Connection * MLV_start_new_connection( 
	const char* server_address, unsigned int port
){
	TODO
	return 0;
}

void MLV_free_connection( MLV_Connection* connection ){
	TODO
}

MLV_Network_msg MLV_send_text(
	MLV_Connection* connection, const char* text, int size
){
	TODO
	return MLV_NET_NONE;
}

MLV_Network_msg MLV_send_integer_array(
	MLV_Connection* connection, int * array, int size
){
	TODO
	return MLV_NET_NONE;
}

MLV_Network_msg MLV_send_real_array(
	MLV_Connection* connection, float* array, int size
){
	TODO
	return MLV_NET_NONE;
}

MLV_Network_msg MLV_get_network_data(
	MLV_Connection* connection, char** message, int** integers, float** reals,
	int* size
){
	TODO
	return MLV_NET_NONE;
}

