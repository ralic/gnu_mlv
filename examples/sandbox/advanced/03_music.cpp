#include <MLV/experimental/window.hpp>


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[] ){
	//
	// Initialise l'infrastructure son de la librairie MLV.
	//
	mlv::audio_center_t audio_center;

	//
	// Charge en mémoire un fichier contenant un morceau de musique.
	//
	mlv::music_t music( "fugue.ogg" );

	//
	// Joue la musique chargée en mémoire.
	//
	audio_center.play_music( music, 1.0, -1 );


	//
	// Attend 20 seconde avant la fin du programme.
	//
	mlv::wait_seconds( 20 );

	//
	// Arrête toutes les musiques en cours d'exécution.
	//
	audio_center.stop_music();

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
