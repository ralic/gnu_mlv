#include <MLV/experimental/window.hpp>


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[] ){
	int width = 640, height = 480;
	int image_width, image_height;

	//
	// On créé et affiche la fenêtre
	//
	mlv::window_t window( "advanced - 6 - image", "image", width, height );

	//
	// On charge en mémoire deux fichiers images.
	//
	mlv::image_t image( "flower.jpg" );

	//
	// On redimensionne les images de sorte à ce que la taille soit la
	// plus grande comprise dans le cadre widthxheight
	//
	image.proportional_resize( width, height);

	//
	// On récupère la nouvelle taille de l'image afin de l'utiliser pour
	// redimensionner la fenêtre.
	//
    image_width = image.width();
	image_height = image.height();

	//
	// On redimensionne la fenêtre
	//
	window.resize( image_width, image_height );

	//
	// On affiche l'image
	//
	window.draw( image, mlv::point_t(0, 0) );

	//
	// Met à jour l'affichage
	//
	window.update();

	//
	// Attend 2 secondes
	//
	window.wait_seconds( 60 );

	return 0;
}

/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2016 Boussicault
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
