#include <MLV/experimental/window.hpp>

//
// Cette fonction réinitialise l'acran puis affiche un texte donnée en 
// parametre à l'écran.
//
void afficher_texte( const std::string & texte, mlv::window_t & window ){
	int size_interline = 9;
	window.clear( mlv::color::black );
	window.draw_text_box( 
		mlv::box::text_t(
			mlv::point_t(10, 10), 
			texte, size_interline,
			mlv::color::black, mlv::color::green, mlv::color::black,
	        mlv::text::left
		)
	);
	window.update();
}

//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[] ){

	mlv::event::key_t key;
	mlv::point_t mouse_position;
	int temps_attente = 5;

	// taille de l'écran
	int width = 640, height = 480;

	mlv::event::event_t event;

	//
	// Créé et affiche la fenêtre
	//
	mlv::window_t window(
		"beginner - 8 - mouse keyboard timer", "mouse keyboard timer",
		width, height
	);

	//
	// Tant que le temps imparti n'est pas écoulé, l'utilisateur est invité à 
	// appuyer sur une touche du clavier
	//
	afficher_texte(
		"Vous passerez à l'écran suivant en:\n"
		"    - appuyant sur une touche du clavier\n"
		"    - attendant quelques secondes.",
		window
	);
	event = window.wait_keyboard_or_seconds( key, temps_attente );
	if( event == mlv::event::key ){
		afficher_texte( "Vous avez choisi le clavier.", window );
	}else{
		afficher_texte( "Le temps est écoulé.", window );
	}
	window.wait_milliseconds( 1500 );


	//
	// Tant que le temps imparti n'est pas écoulé, l'utilisateur est invité à 
	// cliquer sur le bouton gauche de la souris
	//
	afficher_texte(
		"Vous passerez à l'écran suivant en:\n"
		"    - cliquant sur la souris\n"
		"    - attendant quelques secondes.",
		window
	);
	event = window.wait_mouse_or_seconds( mouse_position, temps_attente );
	if( event == mlv::event::mouse_button ){
		afficher_texte( "Vous avez choisi la souris.", window );
	}else{
		afficher_texte( "Le temps est écoulé.", window );
	}
	window.wait_milliseconds( 1500 );

	//
	// L'utilisateur est invité à appuyer sur une touche du clavier ou à 
    // cliquer sur le bouton gauche de la souris.
	//
	afficher_texte(
		"Vous passerez à l'écran suivant en:\n"
		"    - appuyant sur une touche du clavier\n"
		"    - cliquant sur la souris.",
		window
	);
	event = window.wait_keyboard_or_mouse( key, mouse_position );
	if( event == mlv::event::mouse_button ){
		afficher_texte( "Vous avez choisi la souris.", window );
	}else{
		afficher_texte( "Vous avez choisi le clavier.", window );
	}
	window.wait_milliseconds( 1500 );
	
	//
	// Tant que le temps imparti n'est pas écoulé, l'utilisateur est invité à 
    // appuyer sur une touche du clavier ou à cliquer sur le bouton gauche de 
	// la souris.
	//
	afficher_texte(
		"Vous passerez à l'écran suivant en:\n"
		"    - appuyant sur une touche du clavier\n"
		"    - cliquant sur la souris\n"
		"    - attendant quelques secondes.",
		window
	);
	event = window.wait_keyboard_or_mouse_or_seconds(
		key, mouse_position, temps_attente
	);
	if( event == mlv::event::mouse_button ){
		afficher_texte( "Vous avez choisi la souris.", window );
	}else if( event == mlv::event::key ){
		afficher_texte( "Vous avez choisi le clavier.", window );
	}else{
		afficher_texte( "Le temps est écoulé.", window );
	}
	window.wait_milliseconds( 1500 );

	//
	// Tant que le temps imparti n'est pas écoulé, l'utilisateur est invité à 
    // écrire un mot dans la boîte de saisi. 
	//
	afficher_texte(
		"Vous passerez à l'écran suivant en:\n"
		"    - entrant un mot dans la boîte de dialogue;\n"
		"    - attendant quelques secondes.",
		window
	);
	std::string text;
	event = window.wait_input_box_or_milliseconds(                                         
    	mlv::box::input_t(
			mlv::point_t(10, 100), 100, 30,
	    	mlv::color::red, mlv::color::green, mlv::color::black,
    		"Mot : "
		),
		text,
		temps_attente * 1000
	);
	if( event == mlv::event::input_box ){
		afficher_texte(
			"Vous avez choisi la boîte de saisie. Tecte entré : " + text,
			window
		);
	}else{
		afficher_texte( "Le temps est écoulé.", window );
	}
	window.wait_milliseconds( 1500 );

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
