#include <MLV/experimental/window.hpp>
#include <cstdlib>

//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[] ){
	//
	// Créer ne fenetre
	//
	mlv::window_t window( "advanced - 4 - sound", "sound", 640, 480 );

	mlv::audio_center_t audio_center;

	if( ! audio_center.is_valid() ){
		std::cerr << 
			"L'infrasctructure audio de la librairie MLV ne "
			"s'est pas correctement initialisé." << std::endl;
		std::exit(1);
	}

	mlv::sound_t sound( "gallop.ogg" );

	//
	// Affiche la consigne
	//	
	window.draw_text(
		{10,100}, 
		"Appuyer sur une touche pour faire jouer du son.", 
		mlv::color::green
	);
	window.draw_text(
		{10,160},
		"Pour quitter, appuyer sur la touche echap.",
		mlv::color::green
	);
	window.update();

	//
	// Des que l'utilisateur appuye sur une touche, on joue de la musique.
	// Tant que l'utilisateur n'appuye pas sur echap, le programe continue 
	// à tourner
	//
	mlv::event::key_t key;
	while( key.sym != MLV_KEYBOARD_ESCAPE ){
		key = window.wait_keyboard();
		audio_center.play_sound( sound, 1.0 );
	}

	audio_center.stop_all_sounds();

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
