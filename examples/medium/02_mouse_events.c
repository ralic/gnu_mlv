/**
 *
 * Ce programme montre comment il est possible de récupérer des informations
 * provenant de l'utilisateur lorsqu'il utilise sa souris sans bloquer
 * l'exécution du programme.
 *
 * Pour cela il utilise le système d'évènements de la librairie MLV :
 *
 * À chaque fois qu'un utilisateur déplace la sourris, appuie sur les touches 
 * d'un clavier, ou entre du texte dans une boîte de saisie, un événèment 
 * est créé par la librairie MLV. Cet évènement est placé dans une file 
 * d'attente.
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
#include <stdio.h>

//
// Cette fonction affiche sur la fenêtre, le nombre de fois que la souris a été
// déplacé et la position du curseur de la souris.
//
void affichage( int nb, int x, int y, int width, int height ){
	MLV_clear_window( MLV_COLOR_BLACK );
	MLV_draw_text( 10, 10, "Cliquez pour quitter !", MLV_COLOR_GREEN );
	MLV_draw_text(
		10, 40,
		"Nombre de fois que la souris a bougé : %i",
		MLV_COLOR_GREEN, nb
	);
	MLV_draw_text(
		x, y,
		"(%d,%d)",
		MLV_COLOR_GREEN,
		x, y
	);	
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
	int nb= 0 ;
	int x = 0, y = 0;
	MLV_Event event;

	//
	// Créé et affiche une fenêtre
	//
	MLV_create_window(
		"medium - 2 - mouse events", "mouse events", width, height
	);

	//
	// Affichage de la consigne, de la position de la souris et du nombre de
	// fois que la souris a été déplacée
	//
	affichage( nb, x, y, width, height );

	//
	// Tant que l'utilisateur n'a pas cliqué sur la souris, on compte le 
	// nombre de fois que l'utilisateur a déplacé la souris.
	//
	do {
		//
		// Récupère un évènement dans la file des évènements
		// non traités.
		//
		event = MLV_get_event( 
			NULL, NULL, NULL,
			NULL, NULL,
			&x, &y, NULL,
			NULL
		);

		//
		// Traite l'évènement s'il s'agit d'un évènement concernant
		// le déplacement de la souris.
		//
		if( event == MLV_MOUSE_MOTION ){
			//
			// Compte le nombre de fois que la souris a été déplacée.
			//
			nb ++;

			//
			// Affichage de la consigne, de la position de la souris
			//  et du nombre fois que la souris a été déplacée
			//
			affichage( nb, x, y, width, height );
		};
	} while( event != MLV_MOUSE_BUTTON );

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
