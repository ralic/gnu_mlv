#include <MLV/experimental/window.hpp>
#include <stdlib.h>


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main(int argc, char *argv[]){
	std::string text;     // adresse du texte où se trouvera la réponse entrée 
	                      // dans la boîte de saisie par l'utilisateur.
	    // Ici nous n'allouons pas de mémoire. En effet, l'allocation est faite
	    // ultèrieurement par la fonction MLV_wait_input_box().
	    // Nous ne devrons pas oublier de liberer la mémoire à la fin du
	    // programme.
	
	//
	// Créé et affiche la fenêtre
	//
	mlv::window_t window( "beginner - 7 - input box", "input box", 640, 480	);

	//
	// Affiche la question
	//
	window.draw_text(
		mlv::point_t(10, 10), 
		"Veuillez entrer un message dans la fenêtre ci-dessous.",
		mlv::color::green
	);
	window.update();

	//
	// Demande la réponse à la question en utilisant une boîte de saisie
	//
	text = window.wait_input_box(
		mlv::box::input_t(
			mlv::point_t(10,70),
			200, 90,
			mlv::color::red, mlv::color::green, mlv::color::black,
			"message : "
		)
	);


	//
	// Affiche le texte qui a été tapé par l'utilisateur dans la boîte de 
	// saisie
	//
	window.draw_text( mlv::point_t(10, 80), text, mlv::color::green );
	window.update();

	//
	// Attend 2 secondes
	//	
	window.wait_seconds( 2 );
	
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
