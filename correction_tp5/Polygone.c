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

	int i,n;
	{
		printf("Veuillez entrer le nombre d'arêtes du polygone\n");
	}while( scanf("%d",&n) != 1 );

	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window( "Nom_fenetre", "nom_icone", 400, 300 );

	printf("Veuillez donnez à l'aide de la souris les %d points du polygone.\n", n );

	int *vx = (int*) malloc( n*sizeof(int));
	int *vy = (int*) malloc( n*sizeof(int) );
	
	for(i=0; i<n; i++){
		MLV_wait_mouse( vx+i,vy+i );
		MLV_draw_circle(vx[i],vy[i],5,MLV_COLOR_BLUE);
		MLV_actualise_window();
	}

	MLV_draw_polygon(vx,vy,n,MLV_COLOR_RED);
	MLV_actualise_window();

	//
	// Attend 10 secondes avant la fin du programme.
	//
	MLV_wait_seconds( 10 );

	free( vx );
	free( vy );
	//
	// Ferme la fenêtre
	//
	MLV_free_window();

	return 0;
}


