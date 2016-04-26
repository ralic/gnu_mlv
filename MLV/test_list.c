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

#include "list.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
	int cpt;
	int b;
} Data;

void fct( void* data, void* user_data ){
	int* a = (int*) data;
	Data* dt = (Data*) user_data;
	assert( dt->b==42 );
	assert( dt->cpt == *a );
	dt->cpt ++;
}

void count( void* data, void* user_data ){
	int* cpt = (int*) user_data;
	(*cpt)++;
}

//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[] ){

	{
		MLV_List* l = NULL;
		MLV_free_list(l);
	}


	{
		MLV_List* l = NULL;
		l = MLV_prepend_list(l, NULL);
		assert( l );
		MLV_free_list(l);
	}

	{
		int a1 = 1;
		int a2 = 2;
		int a3 = 3;
		int a4 = 4;
		int cpt;

		MLV_List* l0 = NULL;
		MLV_List* l4 = MLV_prepend_list(l0, &a4);
		MLV_List* l3 = MLV_prepend_list(l4, &a3);
		MLV_List* l2 = MLV_prepend_list(l3, &a2);
		MLV_List* l1 = MLV_prepend_list(l2, &a1);
		assert( !l0 );
		assert( l1 );
		assert( l2 );
		assert( l3 );
		assert( l4 );

		assert( ! MLV_find_list( l4, &l3 ) );
		assert( MLV_find_list( l1, &a1 ) == l1 );
		assert( MLV_find_list( l1, &a2 ) == l2 );
		assert( MLV_find_list( l1, &a3 ) == l3 );
		assert( MLV_find_list( l1, &a4 ) == l4 );
		
		assert( ! MLV_find_list( l2, &a1 ) );
		assert( MLV_find_list( l2, &a2 ) == l2 );
		assert( MLV_find_list( l2, &a3 ) == l3 );
		assert( MLV_find_list( l2, &a4 ) == l4 );
		
		assert( ! MLV_find_list( l3, &a1 ) );
		assert( ! MLV_find_list( l3, &a2 ) );
		assert( MLV_find_list( l3, &a3 ) == l3 );
		assert( MLV_find_list( l3, &a4 ) == l4 );

		assert( ! MLV_find_list( l4, &a1 ) );
		assert( ! MLV_find_list( l4, &a2 ) );
		assert( ! MLV_find_list( l4, &a3 ) );
		assert( MLV_find_list( l4, &a4 ) == l4 );

		assert( ! MLV_find_list( l4, &a1 ) );
		assert( ! MLV_find_list( l4, &a2 ) );
		assert( ! MLV_find_list( l4, &a3 ) );
		assert( MLV_find_list( l4, &a4 ) == l4 );

		assert( ! MLV_find_list( l0, &a1 ) );
		assert( ! MLV_find_list( l0, &a2 ) );
		assert( ! MLV_find_list( l0, &a3 ) );
		assert( ! MLV_find_list( l0, &a4 ) );

		Data data;
		data.b = 42;
		data.cpt = 1;

		MLV_foreach_list( l1, fct, &data );

		cpt=0;
		MLV_foreach_list( l1, count, &cpt );
		assert( cpt == 4 );

		MLV_List* l = MLV_remove_list( l1, &a3 );
		assert( l == l1 );

		assert( MLV_find_list( l1, &a1 ) == l1 );
		assert( MLV_find_list( l1, &a2 ) == l2 );
		assert( ! MLV_find_list( l1, &a3 ) );
		assert( MLV_find_list( l1, &a4 ) == l4 );
		
		assert( ! MLV_find_list( l2, &a1 ) );
		assert( MLV_find_list( l2, &a2 ) == l2 );
		assert( ! MLV_find_list( l2, &a3 ) );
		assert( MLV_find_list( l2, &a4 ) == l4 );

		assert( ! MLV_find_list( l4, &a1 ) );
		assert( ! MLV_find_list( l4, &a2 ) );
		assert( ! MLV_find_list( l4, &a3 ) );
		assert( MLV_find_list( l4, &a4 ) == l4 );

		assert( ! MLV_find_list( l0, &a1 ) );
		assert( ! MLV_find_list( l0, &a2 ) );
		assert( ! MLV_find_list( l0, &a3 ) );
		assert( ! MLV_find_list( l0, &a4 ) );

		cpt=0;
		MLV_foreach_list( l1, count, &cpt );
		assert( cpt == 3 );

		MLV_free_list(l1);
	}

	{
		int a1 = 1;
		int a2 = 2;
		int a3 = 3;
		int a4 = 4;
		int cpt;

		MLV_List* l0 = NULL;
		MLV_List* l4 = MLV_prepend_list(l0, &a4);
		MLV_List* l3 = MLV_prepend_list(l4, &a3);
		MLV_List* l2 = MLV_prepend_list(l3, &a2);
		MLV_List* l1 = MLV_prepend_list(l2, &a1);

		MLV_List* l = MLV_remove_list( l1, &a3 );
		assert( l == l1 );

		assert( MLV_find_list( l1, &a1 ) == l1 );
		assert( MLV_find_list( l1, &a2 ) == l2 );
		assert( ! MLV_find_list( l1, &a3 ) );
		assert( MLV_find_list( l1, &a4 ) == l4 );
		
		assert( ! MLV_find_list( l2, &a1 ) );
		assert( MLV_find_list( l2, &a2 ) == l2 );
		assert( ! MLV_find_list( l2, &a3 ) );
		assert( MLV_find_list( l2, &a4 ) == l4 );

		assert( ! MLV_find_list( l4, &a1 ) );
		assert( ! MLV_find_list( l4, &a2 ) );
		assert( ! MLV_find_list( l4, &a3 ) );
		assert( MLV_find_list( l4, &a4 ) == l4 );

		assert( ! MLV_find_list( l0, &a1 ) );
		assert( ! MLV_find_list( l0, &a2 ) );
		assert( ! MLV_find_list( l0, &a3 ) );
		assert( ! MLV_find_list( l0, &a4 ) );

		cpt=0;
		MLV_foreach_list( l1, count, &cpt );
		assert( cpt == 3 );

		MLV_free_list(l);
	}

	{
		int a1 = 1;
		int a2 = 2;
		int a3 = 3;
		int a4 = 4;
		int cpt;

		MLV_List* l0 = NULL;
		MLV_List* l4 = MLV_prepend_list(l0, &a4);
		MLV_List* l3 = MLV_prepend_list(l4, &a3);
		MLV_List* l2 = MLV_prepend_list(l3, &a2);
		MLV_List* l1 = MLV_prepend_list(l2, &a1);

		MLV_List * l = MLV_remove_list( l1, &a1 );
		assert( l == l2 );

		assert( ! MLV_find_list( l2, &a1 ) );
		assert( MLV_find_list( l2, &a2 ) == l2 );
		assert( MLV_find_list( l2, &a3 ) == l3 );
		assert( MLV_find_list( l2, &a4 ) == l4 );

		assert( ! MLV_find_list( l3, &a1 ) );
		assert( ! MLV_find_list( l3, &a2 ) );
		assert( MLV_find_list( l3, &a3 ) == l3 );
		assert( MLV_find_list( l3, &a4 ) == l4 );

		assert( ! MLV_find_list( l4, &a1 ) );
		assert( ! MLV_find_list( l4, &a2 ) );
		assert( ! MLV_find_list( l4, &a3 ) );
		assert( MLV_find_list( l4, &a4 ) == l4 );

		assert( ! MLV_find_list( l0, &a1 ) );
		assert( ! MLV_find_list( l0, &a2 ) );
		assert( ! MLV_find_list( l0, &a3 ) );
		assert( ! MLV_find_list( l0, &a4 ) );

		cpt=0;
		MLV_foreach_list( l, count, &cpt );
		assert( cpt == 3 );

		MLV_free_list(l);
	}

	{
		int a1 = 1;
		int a2 = 2;
		int a3 = 3;
		int a4 = 4;
		int cpt;

		MLV_List* l0 = NULL;
		MLV_List* l4 = MLV_prepend_list(l0, &a4);
		MLV_List* l3 = MLV_prepend_list(l4, &a3);
		MLV_List* l2 = MLV_prepend_list(l3, &a2);
		MLV_List* l1 = MLV_prepend_list(l2, &a1);

		MLV_List * l = MLV_remove_list( l1, &a4 );
		assert( l == l1 );

		assert( MLV_find_list( l1, &a1 ) == l1 );
		assert( MLV_find_list( l1, &a2 ) == l2 );
		assert( MLV_find_list( l1, &a3 ) == l3 );
		assert( ! MLV_find_list( l1, &a4 ) );

		assert( ! MLV_find_list( l2, &a1 ) );
		assert( MLV_find_list( l2, &a2 ) == l2 );
		assert( MLV_find_list( l2, &a3 ) == l3 );
		assert( ! MLV_find_list( l2, &a4 ) );

		assert( ! MLV_find_list( l3, &a1 ) );
		assert( ! MLV_find_list( l3, &a2 ) );
		assert( MLV_find_list( l3, &a3 ) == l3 );
		assert( ! MLV_find_list( l3, &a4 ) );

		assert( ! MLV_find_list( l0, &a1 ) );
		assert( ! MLV_find_list( l0, &a2 ) );
		assert( ! MLV_find_list( l0, &a3 ) );
		assert( ! MLV_find_list( l0, &a4 ) );

		cpt=0;
		MLV_foreach_list( l, count, &cpt );
		assert( cpt == 3 );

		MLV_free_list(l);
	}

	return 0;
}

