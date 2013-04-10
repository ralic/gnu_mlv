/**
 *
 * Ce programme montre comment il est possible de récupérer des informations
 * provenant de l'utilisateur lorsqu'il utilise une boîte de saisie sans bloquer
 * l'exécution du programme.
 *
 * Pour cela il utilise le système d'évènements de la librairie MLV :
 *
 * À chaque fois qu'un utilisateur déplace la sourris, appuie sur les touches 
 * d'un clavier, ou entre du texte dans une boîte de saisie, un événèment 
 * est créé par la librairie MLV.
 * Cet évènement est placé dans une file d'attente.
 * Il est possible de récupérer toutes les informations concernant ces 
 * évènements en appelant la fonction MLV_get_event().
 * Cette fonction supprime le dernier évènement de la pile, l'analyse et 
 * renvoie, à l'aide de ses paramètres et de sa valeur de retour,
 * toutes les informations le concernant.
 *
 * Voici en détail le fonctionnement de la fonction MLV_get_event :
 *
 *------------------------------------------------------------------------------
 * MLV_get_event : 
 *
 *------------------------------------------------------------------------------
 */

#include <MLV/MLV_all.h>
#include <stdlib.h>

//
// Fonction qui s'occupe de l'affichage de la démonstration.
//
void affichage( int width, int height, char* texte1, char* texte2 ){
	//
	// Nettoie l'écran
	//
	MLV_clear_window( MLV_COLOR_BLACK );

	//
	// Affichage de la consigne
	//
	 MLV_draw_adapted_text_box(
		10, 10,
		"Voici un programme qui permet de gérer deux zones de texte simultanément.\nPour quitter, il suffit d'écrire \"quit\" dans la zone de texte de droite.",
		9,
		MLV_COLOR_BLACK, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
		MLV_TEXT_CENTER
	);

	//
	// Affichage du texte qui a été récupéré par la boîte de saisie 1
	//
	MLV_draw_text(
		10, 150,
		texte1,
		MLV_COLOR_GREEN
	);
	
	//
	// Affichage du texte qui a été récupéré par la boîte de saisie 2
	//
	MLV_draw_text(
		220, 150,
		texte2,
		MLV_COLOR_GREEN
	);

	//
	// Dessine tout les boîtes de saisies
	//
	MLV_draw_all_input_boxes();

	//
	// Met à jour l'affichage
	//
	MLV_actualise_window();
}



//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main(int argc, char *argv[]){
	int width = 640, height = 460;
	char* texte, *texte1, *texte2;
	MLV_Input_box *input_box, *input_box_1, *input_box_2;
	MLV_Event event;

	//
	// Créé et affiche une fenêtre
	//
	MLV_create_window(
		"medium - 3 - input box events", "input box events", width, height
	);

	//
	// Créé la première boîte de saisie.
	//
	input_box_1 = MLV_create_input_box(
		10, 100,
		200, 30, 
		MLV_COLOR_GREEN, MLV_COLOR_GREEN,
		MLV_COLOR_BLACK, "Saisie 1 : "
	);
	texte1 = (char*) malloc( 1*sizeof(char) ); *texte1 = '\0';

	//
	// Créé la seconds boîte de saisie.
	//
	input_box_2 = MLV_create_input_box(
		220, 100,
		200, 30, 
		MLV_COLOR_GREEN, MLV_COLOR_GREEN,
		MLV_COLOR_BLACK, "Saisie 2 : "
	);
	texte2 = (char*) malloc( 1*sizeof(char) ); *texte2 = '\0';

	//
	// Met à jour l'affichage
	//
	affichage( width, height, texte1, texte2 );

	//
	// Tant que le texte récupéré par la seconde boîte de saisie est différent 
	// de la chaîne de charactères "quit" on demande à l'utilisateur d'entrer
	// du texte dans un des deux boîtes de saisies et on affiche le texte ainsi
	// rentré. 
	//
	do {
		//
		// Récupère un évènement
		//
		event = MLV_get_event( 
			NULL, NULL, NULL,
			&texte, &input_box,
			NULL, NULL, NULL,
			NULL
		);

		//
		// On traite l'évènement si il s'agit d'une boîte de saisie
		//
		if( event == MLV_INPUT_BOX ){
			//
			// On met à jour le texte associé à la boîte de saisie 1 si c'est
			// la boîte de saisie 1 qui a récupéré le texte
			//
			if( input_box == input_box_1 ){
				//
				// on libère la mémoire pointée par texte1 avant
				// de remplacer texte1 par le pointeur de texte2
				//
				free( texte1 );
				texte1 = texte;
			}

			//
			// On met à jour le texte associé à la boîte de saisie 2 si c'est
			// la boîte de saisie 2 qui a récupéré le texte
			//
			if( input_box == input_box_2 ){
				//
				// on libère la mémoire pointée par texte1 avant
				// de remplacer texte1 par le pointeur de texte2
				//
				free( texte2 );
				texte2 = texte;
			}
		}

		//
		// Met à jour l'affichage
		//
		affichage( width, height, texte1, texte2 );

	} while( strcmp( texte2, "quit" ) );

	//
	// Libère la mémoire utilisée par texte 1 et text 2
	//
	free( texte1 );
	free( texte2 );

	//
	// Ferme toutes les boîtes de saisie.
	//
	MLV_free_input_box( input_box_1 );
	MLV_free_input_box( input_box_2 );

	//
	// Ferme la fenêtre
	//
	MLV_free_window();
	return 0;
}

/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2010,2011,2012,2013 Adrien Boussicault, Marc Zipstein
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
