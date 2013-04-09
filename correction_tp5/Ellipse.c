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

	int width, height;
	int centreX, centreY;
	int rayonX, rayonY;
	{
	printf("Veuillez entrer la hauteur et la largeur de la fenêtre.\n");
	}while( scanf("%d %d",&width,&height) != 2 );

	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window( "Nom_fenetre", "nom_icone", width, height );

	centreX = width/2;
	centreY = height/2;
	
	if( width%2 == 0){
		rayonX = centreX-1;
	}else{
		rayonX = centreX;
	}

	if( height%2 == 0){
		rayonY = centreY-1;
	}else{
		rayonY = centreY;
	}

	MLV_draw_ellipse(
		centreX,
		centreY, 
		rayonX, 
		rayonY, 
		MLV_COLOR_BLUE
	);

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


