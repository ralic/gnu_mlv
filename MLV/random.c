/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2010,2011,2012 Adrien Boussicault, Marc Zipstein
 *   Copyright (C) 2016 Eric Laporte (Bug on MLV_get_random_integer)
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

#include "MLV_random.h"

#ifndef MEMORY_DEBUG
#include <SDL/SDL.h>
#else
#include "memory_debug.h"
#endif

#include <glib.h>

#include "warning_error.h"
#include "memory_management.h"

void MLV_set_seed( int32_t seed ){
	g_random_set_seed(seed);
}

int MLV_get_random_boolean(){
	return g_random_boolean( );
}

int MLV_get_random_integer(int begin, int end){
	return g_random_int_range( begin, end+1 );
}

double MLV_get_random_double(double begin, double end){
	return g_random_double_range( begin, end );
}
