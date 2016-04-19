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

#include "MLV_turtle.h"
#include "turtle.h"
#include <assert.h>
#include <math.h>

//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[] ){

	double error = 0.000000001;

	// Check MLV_create_turtle
	{
		MLV_Turtle* turtle = MLV_create_turtle();
		assert( turtle );
		assert( MLV_turtle_X_coordinate( turtle ) == 0 );
		assert( MLV_turtle_Y_coordinate( turtle ) == 0 );
		assert( MLV_turtle_orientation( turtle ) == 0 );
		assert( ! MLV_turtle_is_writing( turtle ) );
		MLV_free_turtle( turtle );
	}

	// Check MLV_turtle_radian and MLV_turtle_degree
	{
		MLV_Turtle* turtle = MLV_create_turtle();
		assert( turtle );

		MLV_turtle_radian( turtle );
		assert( MLV_turtle_orientation( turtle ) == 0 );

		MLV_turtle_degree( turtle );
		assert( MLV_turtle_orientation( turtle ) == 0 );

		MLV_turtle_orient_to( turtle, 90.0 );
		MLV_turtle_radian( turtle );
		assert( ( MLV_turtle_orientation( turtle ) - M_PI/2.0 ) <= error );

		MLV_turtle_degree( turtle );
		assert( ( MLV_turtle_orientation( turtle ) - 90.0 ) <= error );

		MLV_free_turtle( turtle );
	}

	// Check MLV_turtle_point_to
	{
		MLV_Turtle* turtle = MLV_create_turtle();
		assert( turtle );

		MLV_turtle_go_to( turtle, 20, 10 );
		MLV_turtle_point_to( turtle, 30, 20 );
		assert( ( MLV_turtle_orientation( turtle ) - 45.0 ) <= error );

		MLV_turtle_point_to( turtle, 30, 0 );
		assert( ( MLV_turtle_orientation( turtle ) - (-45.0) ) <= error );

		MLV_turtle_point_to( turtle, 20, 20 );
		assert( ( MLV_turtle_orientation( turtle ) - 90.0 ) <= error );

		MLV_turtle_point_to( turtle, 20, 0 );
		assert( ( MLV_turtle_orientation( turtle ) - (-90.0) ) <= error );

		MLV_turtle_point_to( turtle, 30, 10 );
		assert( ( MLV_turtle_orientation( turtle ) - 0.0 ) <= error );

		MLV_free_turtle( turtle );
	}

	return 0;
}

