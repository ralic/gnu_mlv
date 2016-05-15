#include <MLV/MLV_all.h>

#include <assert.h>

#define DEBUG(x) { fprintf( stderr, "DEBUG : %s - line : %i, file : %s\n", (x), __LINE__, __FILE__ ); }


void add_connection(
	MLV_Connection** connections, int nb_max_connections,
	MLV_Connection* connection
){
	for( int i=0; i< nb_max_connections; i++ ){
		if( connections[i] == NULL ){
			connections[i] = connection;
			break;
		}
	}
}

void treat_incoming_connection(
	MLV_Server* server, MLV_Connection** connections, int nb_max_connections
){
	const char* ip;
	int port;	

	// On regard si il y a de nouvelles connexions/
	MLV_Connection* connection = MLV_get_new_connection( server );
	if( ! connection ) return;  // Il n'y a pas de connexions entrantes
	
	// On récpère des informations sur la connexion entrantes 
	// pour accepter ou refuser la conexion
	MLV_collect_connection_informations( connection, &ip, &port );
	if( strcmp( ip, "100.64.0.1" ) == 0 ){
		// On rejette cette conneexion car on a décidé de bannir l'ip 100.64.0.1.
		MLV_refuse_connection( connection );
		MLV_free_connection( connection );
	}else{
		// On accepte la connection
		MLV_accept_connection( connection );
		// On l'ajoute dans nos structures de donées.
		add_connection( connections, nb_max_connections, connection );
	}
}

void print_network_data( 
	MLV_Network_msg type, char* message, int* integers, float* reals, int size,
	MLV_Connection* connection 
){
	switch( type ){
		case MLV_NET_TEXT :
			printf(
				"Message reçu de %p : %s \n", connection, message
			);
			break;
		case MLV_NET_INTEGERS :
			printf(
				"%d Entiers reçus de %p : \n", size, connection
			);
			for( int j= 0 ; j< size; ) {
				printf( "%d, ", integers[j] );
			}
			break;
		case MLV_NET_REALS :
			printf(
				"%d Réels reçus de %p : \n", size, connection
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

void init_connections_array( 
	MLV_Connection** connections, int nb_max_connections
){
	for( int i=0; i<nb_max_connections; i++ ){
		connections[i] = NULL;
	}
}


void treat_incoming_datas(
	MLV_Connection** connections, int nb_max_connections
){
	int i, size;
	int* integers;
	float* reals;
	char* message;
	MLV_Network_msg type;

	for( i=0; i< nb_max_connections; i++ ){
		if( connections[i] ){
			// We get datas from clients
			type = MLV_get_network_data(
					connections[i], &message, &integers, &reals, &size
			);

			if( type ==  MLV_NET_CONNECTION_DROPED ){
				printf(
					"Connection perdu avec %p. We remove the connection. \n", 
					connections[i]
				);
				MLV_free_connection( connections[i] );
				connections[i] = NULL;
			}else{
				print_network_data(
					type, message, integers, reals, size, connections[i]
				);
				free( message ); free( integers ); free( reals );
			}
		}
	}
}


void send_datas_to_clients(
	MLV_Connection** connections, int nb_max_connections
){
	int i;
	for( i=0; i< nb_max_connections; i++ ){
		if( connections[i] ){
			const char* text_msg = "Coucou";
			MLV_send_text( connections[i], text_msg, strlen(text_msg) );
			int integers_msg[3] = {i, i, i};
			MLV_send_integer_array( connections[i], integers_msg, 3 );
			float reals_msg[3] = {i, i, i};
			MLV_send_real_array( connections[i], reals_msg, 3 );
		}
	}
}

void free_connections( MLV_Connection** connections, int nb_max_connections ){
	for( int i=0; i< nb_max_connections; i++ ){
		if( connections[i] == NULL ){
			MLV_free_connection( connections[i] );
		}
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
	int nb_max_connections = 5;

	// We define the data structure od the conections.
	MLV_Connection* connections[nb_max_connections] ;
	init_connections_array( connections, nb_max_connections );

	MLV_init_network();
	MLV_Server* server = MLV_start_server( port, nb_max_connections );

	int end = 0;
	while( ! end  ){
		// On traite les connexion entrantes
		treat_incoming_connection( server, connections, nb_max_connections );

		// On traite les données envoyées par les clients
		treat_incoming_datas( connections, nb_max_connections );

		// On envoies des données aux clients
		send_datas_to_clients( connections, nb_max_connections );
	}

	free_connections( connections, nb_max_connections );
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
