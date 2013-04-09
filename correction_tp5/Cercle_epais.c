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

#include <MLV/MLV_all.h>

void afficher_cercle_epais( 
	int x, int y, int rayon, int epaisseur, 
	MLV_Color couleur, MLV_Color couleur_fond
){
	MLV_draw_filled_circle(x,y,rayon,couleur);
	MLV_draw_filled_circle(x,y,rayon-epaisseur,couleur_fond);
	MLV_actualise_window();
}

int main( int argc, char *argv[] ){

	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window( "Nom_fenetre", "nom_icone", 400, 300 );

	afficher_cercle_epais( 100, 100, 30, 6, MLV_COLOR_RED, MLV_COLOR_BLACK );

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
