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
#include "MLV_window.h"
#include "MLV_shape.h"
#include "MLV_time.h"

#include "warning_error.h"

#include "memory_management.h"

#include "data_structure.h"

#include "platform.h"

#include "turtle.h"
#include <math.h>

extern DataMLV* MLV_data; 

struct _MLV_Turtle {
	double angle;
	double x;
	double y;
	int write;
	int degree;
	MLV_Color color;
	MLV_Image* image; // The image were the turtle is drawing.
};

struct _MLV_Leonardo_turtle {
	int time;
	int update;
	MLV_Turtle* turtle;
};

void MLV_free_turtle( MLV_Turtle* turtle ){
	MLV_FREE( turtle );
}

MLV_Turtle* MLV_create_turtle(){
	turtle = (MLV_Turtle*) malloc( sizeof(MLV_Turtle) );
	turtle->angle = 0;
	turtle->x = 0;
	turtle->y = 0;
	turtle->write = 0;
	turtle->color = MLV_COLOR_GREEN;
	turtle->degree = 1;
	turtle->image = NULL;
	return turtle;
}

void MLV_turtle_radian( MLV_Turtle* turtle ){
	turtle->degree = 0;
}

void MLV_turtle_degree( MLV_Turtle* turtle ){
	turtle->degree = 1;
}

void MLV_turtle_forward( MLV_Turtle* turtle, float distance ){
	int old_x = turtle->x;
	int old_y = turtle->y;
	if( turtle->degree ){
		turtle->x += distance * cos(turtle->angle * M_PI/180.0 );
		turtle->y += distance * sin(turtle->angle * M_PI/180.0 );
	}else{
		turtle->x += distance * cos(turtle->angle);
		turtle->y += distance * sin(turtle->angle);
	}
	if( turtle->write ){
		if( turtle->image ){
			MLV_draw_line_on_image(
				turtle->image,
				told_x, old_y, turtle->x, turtle->y, turtle->color
			);
			MLV_draw_point_on_image(
				turtle->image,
				old_x, old_y, turtle->color
			);
			MLV_draw_point(
				turtle->image,
				turtle->x, turtle->y, turtle->color
			);
		}else{
			MLV_draw_line( old_x, old_y, turtle->x, turtle->y, turtle->color );
			MLV_draw_point( old_x, old_y, turtle->color );
			MLV_draw_point( turtle->x, turtle->y, turtle->color );
		}
	}
}

void MLV_turtle_right( MLV_Turtle* turtle, double angle ){
	turtle->angle += angle;
}

void MLV_turtle_left( MLV_Turtle* turtle, double angle ){
	turtle->angle -= angle;
}

void MLV_turtle_goto( MLV_Turtle* turtle, int x, int y ){
	turtle->x = x;
	turtle->y = y;
}

void MLV_turtle_color( MLV_Turtle* turtle, MLV_Color color ){
	turtle->color = color;
}

void MLV_write( MLV_Turtle* turtle, int write ){
	turtle->write = write;
}

void MLV_turtle_attach_on_image( MLV_Turtle* turtle, MLV_Image* image ){
	turtle->image = image;
}

void MLV_turtle_orient( MLV_Turtle* turtle, double angle ){
	turtle->angle  = angle;
}

void free_leonardo_turtle(){
	MLV_FREE( MLV_Lenoardo_turtle, MLV_data->leonardo );
	MLV_data->leonardo = NULL;
}

void init_leonardo_turtle(){
	if( MLV_data->leonardo ){
		free_turtle();
	}
	MLV_data->leonardo = MLV_MALLOC( 1, MLV_Leonardo_turtle );

	MLV_data->leonardo->time = 500;
	MLV_data->leonardo->update = 1;

	MLV_data->leonardo->turtle = MLV_create_turtle();
	MLV_turtle_degree( MLV_data->leonardo->turtle );
	MLV_turtle_goto(
		MLV_data->leonardo->turtle,
		MLV_get_window_width()/2, MLV_get_window_height()/2
	);
	MLV_turtle_orient( MLV_data->leonardo->turtle, 0 );
	MLV_turtle_color( MLV_data->leonardo->turtle, MLV_COLOR_GREEN );
	MLV_turtle_write( MLV_data->leonardo->turtle, 1 );
}

void leonardo_updates_window(){
	if( MLV_data->leonardo->update ){
		MLV_update_window();
	}
	if( MLV_data->leonardo->time != 0 ){
		MLV_wait_milliseconds( MLV_data->turtle->time );
	}
}

void MLV_leonardo_radian(){
	MLV_turtle_radian( MLV_data->leonardo->turtle );
}

void MLV_leonardo_degree(){
	MLV_turtle_degree( MLV_data->leonardo->turtle );
}

void MLV_leonardo_forward( float distance ){
	MLV_turtle_forward( MLV_data->leonardo->turtle, distance );
	leonardo_updates_window();
}

void MLV_leonardo_right( double angle ){
	MLV_leonardo_right( MLV_data->leonardo->turtle, angle ); 
	leonardo_updates_window();
}

void MLV_leonardo_left( double angle ){
	MLV_turtle_left( MLV_data->leonardo->turtle, angle );
	leonardo_updates_window();
}

void MLV_leonardo_goto( int x, int y ){
	MLV_turtle_goto( MLV_data->leonardo->turtle, x, y );
	leonardo_updates_window();
}

void MLV_leonardo_orient( double angle ){
	MLV_turtle_orient( MLV_data->leonardo->turtle, angle );
	leonardo_updates_window();
}

void MLV_leonardo_color( MLV_Color color ){
	MLV_turtle_color( MLV_data->leonardo->turtle, color );
}

void MLV_leonardo_write( int write ){
	MLV_turtle_write( MLV_data->leonardo->turtle, write );
}

void MLV_leonardo_speed( int time ){
	MLV_data->leonardo->turtle->time = time;
}

void MLV_leonardo_should_update_window( int yes ){
	MLV_data->leonardo->turtle->update = update;
}
