#include <MLV/MLV_all.h>

#include <assert.h>

#define DEBUG(x) { fprintf( stderr, "DEBUG : %s - line : %i, file : %s\n", (x), __LINE__, __FILE__ ); }

void send_data_to_server( MLV_Connection* connection ){
	const char* text = "Hello from the client !";
	int integers[3] = {42, 42, 42};
	float reals[3] = {3.14, 3.14, 3.14};
	if(
		MLV_send_network_data(
			connections[i], text, strlen(text), integers, 3, reals, 3
		); // TODO strlen ou strlen+1 ?
	){
		pritnf("Data can't be sent.");
	}
}

void print_network_data(
	MLV_Connection*	connection, const char* message, int size_message,
	const int* integers, int size_integers, const float* reals, int size_reals
){
	char* ip;
	int port;
	MLV_collect_connection_informations( connection, &ip, &port );                           

	printf( "Données reçue du serveur %s:%d = \n", ip, port );
	printf( "   - Message : %s\n", size, ip, port );
	printf( "   - Entiers : " );
	printf( "[" );
		for( int j= 0 ; j< size; j++ ) { printf( "%d, ", integers[j] ); }
	printf( "]\n" );
	printf( "   - Réels : " );
	printf( "[" );
		for( int j= 0 ; j< size; j++) { printf( "%.2f, ", reals[j] ); }
	printf( "]\n" );
}

void receive_data_from_server( MLV_Connection* connection ){
	char* message;
	int size_message;

	int* integers;
	int size_integers;

	float* reals;
	int size_reals;

	// We get data from server
	while(
		MLV_receive_network_data(
			connection, 
			&message, &size_message,
			&integers, &size_integers,
			&reals, &size_reals
		) 
	){
		print_network_data(
			connection,
			message, size_message,
			integers, size_integers,
			reals, size_reals
		);
		free( message ); free( integers ); free( reals );
	}
}

//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main(int argc, char *argv[]){
	int port = 10000;
	const char* ip_address = "localhost";

	// On se connecte au serveur
	MLV_init_network();
	MLV_Connection * connection= MLV_start_new_connection( ip_address, port );
	if( ! connection ){
		fprintf(
			stderr, "The connection to the server is not possible."
			" The server is not open or the network doesn't work.\n"
		);
		exit(1);
	}

	while( ! MLV_connection_is_lost( connection ) ){
		MLV_wait_milliseconds(1000);

		// On récupére les données envoyées par le serveurs
		receive_data_from_server( connection );

		// On envoie des messages au serveur
		send_data_to_server( connection );
	}

	MLV_free_connection( connection );
	MLV_free_network();

	return 0;
}

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
