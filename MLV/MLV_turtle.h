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

/** \~french 
 * \file MLV_turtle.h
 *
 * \author Adrien Boussicault
 *
 * \brief Ce fichier définit les prototypes des fonctions permettant de 
 *        manipuler des tortues fonctionnant comme les tortues de langage Logo.
 */

#ifndef __MLV__MLV_TURTLE_H__
#define __MLV__MLV_TURTLE_H__

#include "MLV_color.h"
#include "MLV_Image.h"

#ifdef __cplusplus
extern "C" {
#endif

void MLV_leonardo_radian();
void MLV_leonardo_degree();
void MLV_leonardo_forward( float distance );
void MLV_leonardo_right( double angle );
void MLV_leonardo_left( double angle );
void MLV_leonardo_goto( int x, int y );
void MLV_leonardo_orient( double angle );
void MLV_leonardo_color( MLV_Color color );
void MLV_leonardo_write( int write );
void MLV_leonardo_speed( int time );
void MLV_leonardo_should_update_window( int yes );

typedef struct _MLV_Turtle MLV_Turtle;

MLV_Turtle* MLV_create_turtle();

void MLV_free_turtle( MLV_Turtle* turtle );
void MLV_turtle_attach_on_image( MLV_Turtle* turtle, MLV_Image* image );
void MLV_turtle_radian( MLV_Turtle* turtle );
void MLV_turtle_degree( MLV_Turtle* turtle );
void MLV_turtle_forward( MLV_Turtle* turtle, float distance );
void MLV_turtle_right( MLV_Turtle* turtle, double angle );
void MLV_turtle_left( MLV_Turtle* turtle, double angle );
void MLV_turtle_goto( MLV_Turtle* turtle, int x, int y );
void MLV_turtle_orient( MLV_Turtle* turtle, double angle );
void MLV_turtle_color( MLV_Turtle* turtle, MLV_Color color );
void MLV_turtle_write( MLV_Turtle* turtle, int write );

#ifdef __cplusplus
}
#endif

#endif
