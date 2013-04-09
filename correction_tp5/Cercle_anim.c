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

int main( int argc, char *argv[] ){

	int width = 640, height=480;
	int posX, posY;
	int pas;
	int rayon;
	{
		printf("Veuillez entrer la hauteur et la largeur de la fenêtre.\n");
	}while( scanf("%d %d",&width,&height) != 2 );
	{
		printf("Veuillez entrer le pas pour afficher les cercles\n");
	}while( scanf("%d",&pas) != 1 );

	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window( "Nom_fenetre", "nom_icone", width, height );

	posX = width/2;
	posY = height/2;
	rayon = pas;
	while( ( rayon < width/2 ) && ( rayon < height/2 ) ){
		MLV_draw_circle( posX, posY, rayon, MLV_COLOR_RED);
		MLV_actualise_window();
		rayon = rayon + pas;
		MLV_wait_milliseconds( 500 );
	}

	MLV_wait_seconds( 2 );

	//
	// Ferme la fenêtre
	//
	MLV_free_window();

	return 0;
}
