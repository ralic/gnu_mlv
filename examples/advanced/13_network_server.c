#include <MLV/MLV_all.h>

#include <assert.h>

#define DEBUG(x) { fprintf( stderr, "DEBUG : %s - line : %i, file : %s\n", (x), __LINE__, __FILE__ ); }

int connection_filter(
	MLV_Server* server, const char* ip, int port, void* data
){
	// Cette fonction est un filtre que l'on enregistre auprès du serveur 
	// pour accpeter ou refuser les connexions.
	// Cette fonction doit renvoyer Vrai si vous voulez que la connection 
	// soit acceptée.
	if( strcmp( ip, "100.64.0.1" ) == 0 ){
		return 0;  // Connection refusée ! On ne fait pas confiance à 100.64.0.1.
	}else{
		return 1; // Connection acceptée !
	}
}

void treat_incoming_connection(
	MLV_Server* server, MLV_Connection** connections, int nb_max_connections
){
	// On récupère toutes les nouvelles connexions entrantes et on les 
	// enregistre dans nos structures de données.
	MLV_Connection* connection;
	while( connexion = MLV_get_new_connection( server ) ){
		// On enregiste la connexion dans nos structures de données.
		//     Comme le serveur est configuré pour n'accepter que 
		//     nb_max_connecions, nous somms sur que la table connections 
		//     contients un champs vide (un champs à NULL).
		for( int i=0; i< nb_max_connections; i++ ){
			if( connections[i] == NULL ){
				connections[i] = connection;
				break;
			}
		}
	}
}

void treat_lost_connection(
	MLV_Connection** connections, int nb_max_connections
){
	for( int i=0; i< nb_max_connections; i++ ){
		if( connections[i] && MLV_connection_is_lost( connections[i] ) ){
			MLV_free_connection( connections[i] );
			connections[i] = NULL;
			break;
		}
	}
}

void print_network_data(
	MLV_Connection*	connection, const char* message, int size_message,
	const int* integers, int size_integers, const float* reals, int size_reals
){
	char* ip;
	int port;
	MLV_collect_connection_informations( connection, &ip, &port );                           

	printf( "Données reçue de %s:%d = \n", ip, port );
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

void treat_incoming_datas(
	MLV_Connection** connections, int nb_max_connections
){
	char* message;
	int size_message;

	int* integers;
	int size_integers;

	float* reals;
	int size_reals;

	for( i=0; i< nb_max_connections; i++ ){
		if( connections[i] ){
			// On récupère et affiche toutes les données envoyées par le client 
			// numéro 'i'
			while(
				MLV_get_network_data(
					connections[i], 
					&message, &size_message,
					&integers, &size_integers,
					&reals, &size_reals
				) 
			){
				print_network_data(
					connections[i],
					message, size_message,
					integers, size_integers,
					reals, size_reals
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
			const char* text = "Hello from the server !";
			int integers[3] = {i, i, i};
			float reals[3] = {i*1.11, i*1.11, i*1.11};
			if(
				MLV_send_data(
					connections[i], text, strlen(text), integers, 3, reals, 3
				); // TODO strlen ou strlen+1 ?
			){
				pritnf("Data can't be sent.");
			}
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
	int nb_max_connections = 5;

	// On définit le tableau qui contiendra toutes les connexions entre le 
	// serveur et les clients.
	MLV_Connection* connections[nb_max_connections] ;
	for( int i=0; i<nb_max_connections; i++ ) connections[i] = NULL;

	// On initialise et demmare un serveur qui écoutera sur le port 10000.
	//     Quand on veut envoyer un message à un ordinateur, on a besoin de 
	//     1) dire à quel ordinateur
	//     2) dire quelle application doit lire le message
	//
	//     Pour désinger un ordinateur sur le réseau on utilise l'adresse IP.
	//     Il s'agit de 4 chiffres comme 147.210.215.26. Cette addresse ip 
	//     identifie un ordinateur sur le réseau. Ce code n'est pas
	//     très lisble pour un homme. Elle est souvent remplacé par une
	//     chaîne de caractère plus explicite. Par exemple www.u-bordeaux.fr
	// 
	//     Pour désigner une application, on utilise un entier appellé port.
	//     Quand une application ouvre une connection, elle définit un port
	//     qui permettra au système d'exploitation de rediriger tous les 
	//     messages sur ce port.
	//     Par exemple, pour envoyer les requêttes http aux sites que vous 
	//     consultez sur internet, firefox utilise le port 80, car les 
	//     application web utilisent généralement le port 80.
	//     Cependant, il est possible de dire à firefox d'envoyer les requêtes
	//     sur un autre port, il vous suffit de taper l'adress web suivit de 
	//     :PORT où PORT est le nouveau port.
	//     Par exemple, vous pouvez essayer de taper http://www.u-bordeau.fr:324
	//     Comme il n'y a pas d'application WEB qui écoute sur le port 324, 
	//     votre navigateur web devrait ne pas trouver de pages.
	//     Par exemple, si vous êtes sous Linux ou MacOSX, il est fotement 
	//     probable que le serveur Web CUPS est en train de tourner. C'est
	//     le serveur qui s'occupe de gérer les impressions.
	//     Vous pouvez y acceder en utilisant :
	//     - l'addresse "localhost" qui est le nom que l'on donne à la machone
	//       courante.
	//     - le port 632.
	//     Essayer de taper dans votre navigateur web : localhost:631 .
	int port = 10000;
	MLV_init_network();
	MLV_Server* server = MLV_start_server( port, nb_max_connections );

	// On enregiste un filtre de connections pour refuser les connections
	// provenant d'adresses ip indésirables.
	// Cette ligne est optionnelle et peut être enlevée si vous n'avez pas 
	// besoin de filtrer les connections entrantes.
	MLV_set_connection_filter( server, connection_filter, NULL );

	int end = 0;
	while( ! end  ){
		// On décide que le serveur traitera les connections toutes les secondes.
		MLV_wait_milliseconds(1000);

		// On traite les connexion qui ont étés coupées
		treat_lost_connection( connections, nb_max_connections );

		// On traite les connexion entrantes
		treat_incoming_connection( server, connections, nb_max_connections );

		// On traite les données envoyées par les clients
		treat_incoming_datas( connections, nb_max_connections );

		// On envoies des données aux clients
		send_datas_to_clients( connections, nb_max_connections );
	}

	for( int i=0; i< nb_max_connections; i++ ){
		MLV_free_connection( connections[i] ); // connecitons[i] can be 0.
	}
	MLV_free_server( server );
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
