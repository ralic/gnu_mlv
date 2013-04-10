/**
 * Cette dmonstration explique comment l'utilisateur peut faire pour travailler
 * avec les chemins d'acces des fichiers.
 *
 *------------------------------------------------------------------------------
 * MLV_get_base_name : 
 *
 *------------------------------------------------------------------------------
 * MLV_get_directory_name : 
 *
 *------------------------------------------------------------------------------
 * MLV_path_is_absolute : 
 *
 *------------------------------------------------------------------------------
 * MLV_path_is_relative : 
 *
 *------------------------------------------------------------------------------
 * MLV_path_exists : 
 *
 *------------------------------------------------------------------------------
 * MLV_path_is_a_directory : 
 *
 *------------------------------------------------------------------------------
 * MLV_path_is_a_file : 
 *
 *------------------------------------------------------------------------------
 * MLV_build_path : 
 *
 *------------------------------------------------------------------------------
 * MLV_get_current_directory : 
 *
 *------------------------------------------------------------------------------
 * MLV_get_temporary_directory : 
 *
 *------------------------------------------------------------------------------
 * MLV_get_home_directory : 
 *
 *------------------------------------------------------------------------------
 *
 */

#include <MLV/MLV_all.h>
#include <stdio.h>

//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main(int argc, char *argv[]){

	printf( "\n" );
	
	const char *current_directory, *temporary_directory, *home_directory;
	
	current_directory = MLV_get_current_directory( );
	printf("Répertoire courant : %s \n", current_directory);

	temporary_directory = MLV_get_temporary_directory( );
	printf( "Répertoire temporaire : %s\n", temporary_directory );

	home_directory = MLV_get_home_directory( );
	printf( "Répertoire personnel : %s\n", home_directory );

	const char* path = "./creature.png";
	if( MLV_path_exists( path ) ){
		printf("Le chemin %s existe.\n", path );
	}else{
		printf("Le chemin %s n'existe pas.i\n", path );
	}

	if( MLV_path_is_a_file( path ) ){
		printf("%s est un fichier.\n", path );
	}else{
		printf("%s n'est pas un fichier.\n", path );
	}

	if( MLV_path_is_a_directory( path ) ){
		printf("%s est un répertoire.\n", path );
	}else{
		printf("%s n'est pas un repertoire.\n", path );
	}

	if(
		MLV_path_is_absolute( path )
  	){
		printf( "%s  est un chemin absolu.\n", path );
	}else{
		printf( "%s est un chemin relatif.\n", path );
	}
	char* build_path = MLV_build_path( current_directory, path, NULL );
	if(
		MLV_path_is_relative( build_path )
  	){
		printf( "%s est un chemin relatif.\n", build_path );
	}else{
		printf( "%s est un chemin absolu.\n", build_path );
	}

	char* basename = MLV_get_base_name( build_path );
	char* dirname = MLV_get_directory_name( build_path );
	printf( "Dans la chemin précédent,\n" );
	printf( "La chaîne de texte se trouvant après le dernier séparateur / est : %s\n", basename );
	printf( "La chaîne de texte s'étendant jusqu'au dernier séparateur / est : %s\n", dirname );

	printf( "\n" );
	
	free( build_path );
	free( basename );
	free( dirname );

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
