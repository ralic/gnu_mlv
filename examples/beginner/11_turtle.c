/**
 *
 * Ce programme utilise la tortue Leonardo pour réaliser des dessins.
 *
 * Pour cela le programme  utilise les fonctions suivantes : 
 *
 *------------------------------------------------------------------------------
 * 
 *   TODO : Ecrire la documentiation des fonctions
 * 
 *------------------------------------------------------------------------------
 */

#include <MLV/MLV_all.h>


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[] ){

	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window( "beginner - 11 - The turtle", "Th turtle", 640, 480 );

	// On affiche la tortue Léonardo (c'est optionnel, la tortue est plus facile
	// A diriger lorsqu'on la voit.
	MLV_show_leonardo();

	// On change la couleur du pinceau 
	MLV_leonardo_color( MLV_COLOR_GREEN );

	// On change la vitesse de Leonardo en modifiant le temps en miliseconde
	// pris par la tortue entre chaque déplacement ( left, right, orient_to, 
	// go_to ou forward ).
	MLV_leonardo_speed(200);

	//
	// Nous allons faire tracer par la tortue Léonardo un triangle équilatéral.
	//

	// On déplace la tortue à la coordonnée (x=200, y=100)
	MLV_leonardo_go_to( 200, 100 );
	// On oriente Leonardo vers le bas de l'image.
	MLV_leonardo_orient_to( 90 );

	// Dessin du premier côté du triangle :
	// On pose le crayon su l'écran
	MLV_leonardo_write(1); 
	// on demande à la tortue d'avancer de 300 pixel
	MLV_leonardo_forward(300);
	
	// Dessin du deuxième côté du triangle
	// On tourne de 120 degrés à gauche
	MLV_leonardo_left(120);
	// On trace le côté en faisant avancer la tortue
	MLV_leonardo_forward(300);

	// Dessin du troisième côté du triangle
	MLV_leonardo_left(120);
	MLV_leonardo_forward(300);
	
	//
	// On attend 10 secondes avant d'arêter le programme en libérant la fenêtre.
	//
	MLV_wait_seconds( 10 );
	MLV_free_window();

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
