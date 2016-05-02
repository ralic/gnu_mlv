#include <MLV/MLV_all.h>

#define DEBUG(x) { fprintf( stderr, "DEBUG : %s - line : %i, file : %s\n", (x), __LINE__, __FILE__ ); }

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

	// L'utilisateur Toto se connecte au serveur
	MLV_Server_connection * connection_toto = MLV_connect_to_server(
		ip_address, port, "Toto"
	);
//	if( ! MLV_connection_is_up( connection_toto) ){
//		fprintf( stderr, "Conection to server was a failure.");
//		exit(1);
//	}

	// L'utilisateur Tutu se connecte au serveur
	MLV_Server_connection * connection_tutu = MLV_connect_to_server(
		ip_address, port, "Tutu"
	);
//	if( ! MLV_connection_is_up( connection_tutu ) ){
//		fprintf( stderr, "Conection to server was a failure.");
//		exit(1);
//	}

	while(1){
		MLV_wait_seconds(1);
		// Toto envoie un message à Tutu
		const char* tutu = "Tutu";
		const char* message = "Message interessant !";
		int success = MLV_send_message_to_network(
			connection_toto, tutu, message
		);
		if( success ){
			printf(
				"Le message envoyé %s a bien été envoyé à %s.", tutu, message
			);	
		}

		char* text;
		int integer;
		float real;
		const char* expeditor;
		MLV_Network_data_type type = MLV_get_network_data(
			connection_tutu, &text, &integer, &real, &expeditor
		);
		if( type == MLV_NET_NONE ){
			printf("%s Aucun message reçu.\n", tutu);
		}
		if( type == MLV_NET_TEXT ){
			printf(
				"%s a reçu le message de %s suivant : %s.\n", 
				tutu, expeditor, text
			);
			free( text );
		}
		if( type == MLV_NET_INTEGER ){
			printf(
				"%s a reçu l'entier de %s suivant : %d.\n", 
				tutu, expeditor, integer
			);
		}
		if( type == MLV_NET_REAL ){
			printf(
				"%s a reçu le réel de %s suivant : %f.", 
				tutu, expeditor, real
			);
		}
	}

	MLV_disconect( connection_tutu );
	MLV_disconect( connection_toto );

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
