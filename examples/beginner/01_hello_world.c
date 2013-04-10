/**
 *
 * Ce programme créé une fenêtre et affiche Bonjour.
 *
 * Pour cela le programme  utilise les fonctions suivantes : 
 *
 *------------------------------------------------------------------------------
 * MLV_create_window : 
 *
 *------------------------------------------------------------------------------
 * MLV_free_window : 
 *
 *------------------------------------------------------------------------------
 * MLV_actualise_window : 
 * 
 *------------------------------------------------------------------------------
 * MLV_draw_text : 
 *
 *------------------------------------------------------------------------------
 *
 * Il existe d'autres fonctions pour afficher du texte. Vous les trouverez en 
 * consultant le fichier MLV_text.h ou en tapant dans un terminal la commande :
 *
 * man MLV_text.h
 *
 *
 * Le programme peut aussi attendre un certain nombre de secondes en utilisant
 * la fonction :
 *
 *------------------------------------------------------------------------------
 * MLV_wait_seconds : 
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
	MLV_create_window( "beginner - 1 - hello world", "hello world", 640, 480 );

	//
	// Affiche "Bonjour !" a l'écran 
	//
	MLV_draw_text(
		10, 120, 
		"Bonjour !",
		MLV_COLOR_MAGENTA
	);

	//
	// Met a jour l'affichage.
	//
	MLV_actualise_window();

	//
	// Attend 10 secondes avant la fin du programme.
	//
	MLV_wait_seconds( 10 );

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
