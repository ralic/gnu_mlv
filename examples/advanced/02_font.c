/**
 *
 * Ce programme explique comment utiliser de nouvelles polices de caractères 
 * pour afficher du texte.
 *
 * La police de caractère par default est DejaVuSerif-Bold. Il n'est pas 
 * possible de changer ou supprimer la police par default mais, les fonctions 
 * suivantes vous explique comment charger une nouvelle police et comment 
 * l'utiliser pour afficher du texte avec cette dernière.
 *
 *------------------------------------------------------------------------------
 * MLV_load_font : 
 *
 *------------------------------------------------------------------------------
 * MLV_free_font : 
 *
 *------------------------------------------------------------------------------
 * MLV_draw_text_with_font : 
 *
 *------------------------------------------------------------------------------
 */



#include <MLV/MLV_all.h>


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// Il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[]){
	//
	// Créé et affiche la fenetre
	//
	MLV_create_window( "advanced - 2 - font", "font", 640, 480 );
	
	//
	// Charge une font en mémoire
	//
	MLV_Font* font = MLV_load_font( "Garuda-Oblique.ttf" , 20 );

	//
	// Affiche un texte avec la font qui vient d'être chargée
	//
	MLV_draw_text_with_font(
		10, 10,
		"Le texte est écrit avec la font Garuda-Oblique.", 
		font, MLV_COLOR_GREEN
	);

	//
	// Met à jour l'affichage de la fenêtre
	//
	MLV_actualise_window();

	//
	// Attend 5 seconde avant la fin du programme.
	//
	MLV_wait_seconds( 5 );


	//
	// Ferme proprement la font qui a été chargée en mémoire durant le 
	// programme.
	//
	MLV_free_font( font );

	//
	// Ferme la fenetre
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
