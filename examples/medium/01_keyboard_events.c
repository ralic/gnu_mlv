/**
 *
 * Ce programme montre comment il est possible de récupérer des informations
 * provenant de l'utilisateur lorsqu'il utilise son clavier sans bloquer
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
#include <stdio.h>

//
// Fonction qui s'occupe de l'affichage de la démonstration.
//
void affichage( int nb, int width, int height ){
	//
	// Nettoie l'écran pour un nouvel affichage
	//
	MLV_clear_window( MLV_COLOR_BLACK );

	//
	// Affiche la consigne
	//
	MLV_draw_text(
		10, 10,
		"Appuyer sur     shift+q     et     relâcher uniquement la touche q     pour quitter !",
		MLV_COLOR_GREEN
	);

	//
	// Affiche le nombre de fois qu'une touche a été appuyée depuis le debut
	// du programme.
	//
	MLV_draw_text(
		10, 40, 
		"Nombre de fois que l'on a appuyé sur une touche : %i",
		MLV_COLOR_GREEN,
		nb
	);

	//
	// Met à jour la fenêtre
	//
	MLV_actualise_window();
}


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh, il faut, 
// pour la déclaration du main, respecter strictement la syntaxe suivante :
//
int main(int argc, char *argv[]){
	int width = 640, height = 460;    //Taille de la fenêtre
	int nb= 0 ;             // Nombre de fois qu'une touche a été appuyée

	// informations conernant les évènements de typeclavier.
	MLV_Keyboard_modifier mod;
	MLV_Keyboard_button sym;
	MLV_Button_state state;
    
	// Variable contenant le code associé au type d'un évènement.
	MLV_Event event;
	
	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window(
		"medium - 1 - keyboard events", "keyboard events", width, height
	);

	//
	// Met a jour l'affichage
	//
	affichage( nb, width, height );

	
	//
	// On compte le nombre de fois que l'utilisateur a appuyé sur une
	// touche.
	// On s'arrête quand la touche q a été rélachée suite à une combinaison 
	// shift+q.
	//
	do {
		//
		// Récupère un évènement dans la file des évènements
		// non traités.
		//
		event = MLV_get_event( 
			&sym, &mod, NULL, 
			NULL, NULL,
			NULL, NULL, NULL,
			&state
		);

		//
		// Traite l'évènement s'il s'agit d'un évènement clavier
		//
		if( event == MLV_KEY ){
			//
			// Compte le nombre de fois qu'une touche a été
			// préssée.
			//
			if( state == MLV_PRESSED ){
				nb ++;
			}

			//
			// Met à jour l'affichage
			//
			affichage( nb , width, height );
		};
	} while(
		!(
			( sym == MLV_KEYBOARD_q ) &&
			MLV_shift_key_was_pressed( mod ) &&
			( state == MLV_RELEASED )
		) 
	);

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
