#include <MLV/MLV_all.h>

#include <assert.h>

#define DEBUG(x) { fprintf( stderr, "DEBUG : %s - line : %i, file : %s\n", (x), __LINE__, __FILE__ ); }

void send_datas_to_server( MLV_Connection* connection ){
	const char* text_msg = "Hi !";
	MLV_send_text( connection, text_msg, strlen(text_msg) );
	int integers_msg[3] = {42, 42, 42};
	MLV_send_integer_array( connection, integers_msg, 3 );
	float reals_msg[3] = {3.14, 3.14, 3.14};
	MLV_send_real_array( connection, reals_msg, 3 );
}

void print_network_data( 
	MLV_Network_msg type, char* message, int* integers, float* reals, int size
){
	switch( type ){
		case MLV_NET_TEXT :
			printf(
				"Message reçu du serveur : %s \n", message
			);
			break;
		case MLV_NET_INTEGERS :
			printf(
				"%d Entiers reçus du serveur : \n", size
			);
			for( int j= 0 ; j< size; ) {
				printf( "%d, ", integers[j] );
			}
			break;
		case MLV_NET_REALS :
			printf(
				"%d Réels reçus du serveur : \n", size
			);
			for( int j= 0 ; j< size; ) {
				printf( "%f, ", reals[j] );
			}
			break;
		default:;
			fprintf(stderr, "This case is not possible\n");
			assert(0);
	}
}

int get_data_from_server( MLV_Connection* connection ){
	int end, size;
	int* integers;
	float* reals;
	char* message;

	// We get datas from clients
	MLV_Network_msg type = MLV_get_network_data(
			connection, &message, &integers, &reals, &size
	);

	if( type ==  MLV_NET_CONNECTION_DROPED ){
		printf( "Connection perdu avec le serveur." );
		end = 1;
	}else{
		print_network_data( type, message, integers, reals, size );
		free( message ); free( integers ); free( reals );
		end = 0;
	}
	return end;
}

//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main(int argc, char *argv[]){

	MLV_init_network();

	int port = 10000;
	const char* ip_address = "localhost";

	// On se connecte au serveur
	MLV_Connection * connection= MLV_start_new_connection( ip_address, port );

	int end = 0;
	while( ! end ){
		MLV_wait_seconds(1);

		// On récupére les données envoyées par le serveurs
		end = get_data_from_server( connection );

		// On envoie des messages au serveur
		send_datas_to_server( connection );
	}

	MLV_free_connection( connection );
	MLV_free_network();

	return 0;
}

/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2014 Adrien Boussicault, Marc Zipstein
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
