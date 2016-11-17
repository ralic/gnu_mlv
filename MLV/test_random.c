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

#include "MLV_random.h"
#include <assert.h>
#include <stdlib.h>

void test_integer_random( int min, int max, int32_t seed, int nb_try ){
	MLV_set_seed( seed );
	int range = max-min+1;
	int* pres = (int*) calloc( range, sizeof(int) );
	assert(pres);
	for( int i=0; i<nb_try; i++ ){
		int entier = MLV_get_random_integer(min,max);
		assert( ( min <= entier ) && (entier <= max) );
		pres[ entier-min ] = 1;
	}
	for(int i=min; i<=max; i++){
		assert( pres[i-min] );
	}
	free(pres);
}

//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[] ){

	test_integer_random( 0, 10, 0, 10000 );
	test_integer_random( 3, 9, 0, 10000 );
	test_integer_random( -3, 4, 0, 10000 );
	test_integer_random( -5, -3, 0, 10000 );

	return 0;
}

