#include <MLV/experimental/window.hpp>


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main(int argc, char *argv[]){
	//
	// Déclaration de la variable qui représentera le code de la touche qui
	// sera appuyée par l'utilisateur.
	//
	mlv::event::key_t touche;

	//
	// Créé et affiche la fenêtre
	//
	mlv::window_t window( "beginner - 6 - keyboard", "keyboard", 640, 480 );

	//
	// Affiche la consigne
	//
	window.draw_text( mlv::point_t(10, 10), "Appuyez sur la touche k", mlv::color::green );
	window.update();

	//
	// Attendre que l'utilisateur appuie sur une touche du clavier
	//
	window.wait_keyboard( touche );

	//
	// Affiche "Bien !" si l'utilisateur a appuyer sur la touche k sinon
	// affiche un message d'erreur.
	//
	if( touche.sym == MLV_KEYBOARD_k ){
		window.draw_text( mlv::point_t(10, 30), "Bien !", mlv::color::green );
	}else{
		window.draw_text( 
			mlv::point_t(10, 30), "Vous n'avez pas appuyé sur la touche k",
			mlv::color::green
		);
	}
	window.update();
	
	//
	// Attend 2 seconde avant la fin du programme.
	//
	window.wait_seconds( 2 );
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
