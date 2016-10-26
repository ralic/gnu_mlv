#include <MLV/experimental/window.hpp>


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
	mlv::window_t window( "beginner - 11 - The turtle", "Th turtle", 640, 480 );

	// On affiche la tortue Léonardo (c'est optionnel, la tortue est plus facile
	// A diriger lorsqu'on la voit.
	window.show_leonardo();

	// On change la couleur du pinceau 
	window.set_leonardo_color( mlv::color::green );

	// On change la vitesse de Leonardo en modifiant le temps en miliseconde
	// pris par la tortue entre chaque déplacement ( left, right, orient_to, 
	// go_to ou forward ).
	window.set_leonardo_speed(200);

	//
	// Nous allons faire tracer par la tortue Léonardo un triangle équilatéral.
	//

	// On déplace la tortue à la coordonnée (x=200, y=100)
	window.leonardo_go_to( {200, 100} );
	// On oriente Leonardo vers le bas de l'image.
	window.leonardo_orient_to( 90 );

	// Dessin du premier côté du triangle :
	// On pose le crayon su l'écran
	window.leonardo_write(true); 
	// on demande à la tortue d'avancer de 300 pixel
	window.leonardo_forward(300);
	
	// Dessin du deuxième côté du triangle
	// On tourne de 120 degrés à gauche
	window.leonardo_left(120);
	// On trace le côté en faisant avancer la tortue
	window.leonardo_forward(300);

	// Dessin du troisième côté du triangle
	window.leonardo_left(120);
	window.leonardo_forward(300);
	
	//
	// On attend 10 secondes avant d'arêter le programme en libérant la fenêtre.
	//
	window.wait_seconds( 10 );

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
