#include <MLV/experimental/window.hpp>


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main(int argc, char *argv[]){
	//
	// Créé et affiche la fenêtre
	//
	mlv::window_t window( "beginner - 2 - shapes", "shapes", 640, 480 );
	
	//
	// Dessine des cercles, ellipses, rectangles, lignes et points
	//
	window.draw_circle( mlv::point_t(20, 20), 10, mlv::color::purple );
	window.draw_filled_circle( mlv::point_t(50, 20), 10, mlv::color::brown );
	window.draw_ellipse( mlv::point_t(100, 20), 30, 10, mlv::color::cyan );
	window.draw_filled_ellipse( mlv::point_t(170, 20), 30, 10, mlv::color::pink );
	window.draw_rectangle( mlv::point_t(10, 50), 40, 20, mlv::color::blue );
	window.draw_filled_rectangle( mlv::point_t(70, 50), 40, 20, mlv::color::green );
	window.draw_line( mlv::point_t(120, 50), mlv::point_t(160, 90), mlv::color::white );
	window.draw_point( mlv::point_t(10, 110), mlv::color::red );

	//
	// Dessine une courbe de Bézier avec ses sommets
	//
	mlv::point_t points[4] = {
		mlv::point_t(10, 150), mlv::point_t(50, 190), 
		mlv::point_t(90, 150), mlv::point_t(130, 190)
	};
	window.draw_bezier_curve( points, 4, mlv::color::red );
	window.draw_circle( points[0], 3, mlv::color::green );
	window.draw_circle( points[1], 3, mlv::color::green );
	window.draw_circle( points[2], 3, mlv::color::green );
	window.draw_circle( points[3], 3, mlv::color::green );

	//Dessine un polygone avec ses sommets
	mlv::point_t points1[4] = { 
		mlv::point_t(200, 150), mlv::point_t(240, 190), 
		mlv::point_t(320, 190), mlv::point_t(280, 150)
	};
	window.draw_filled_polygon( points1, 4, mlv::color::blue );
	window.draw_polygon( points1, 4, mlv::color::red );
	window.draw_circle( points1[0], 3, mlv::color::green );
	window.draw_circle( points1[1], 3, mlv::color::green );
	window.draw_circle( points1[2], 3, mlv::color::green );
	window.draw_circle( points1[3], 3, mlv::color::green );

	//
	// Affiche du texte
	//
	window.draw_text(
		mlv::point_t(10, 120), 
		"Juste au dessus de cette ligne, il y a un pixel rouge.",
		mlv::color::magenta
	);

	//
	// Met à jour l'affichage.
	//
	window.update();

	//
	// Attend 10 secondes avant la fin du programme.
	//
	window.wait_seconds( 10 );

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
