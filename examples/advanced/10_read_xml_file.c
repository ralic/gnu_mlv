/**
 * Ce programme explique commen utilise l'interface simplifié de la librairie
 * pour lire et recupere des informations contenu dans des fichiers écrits au
 * format xml.
 *
 * -----------------------------------------------------------------------------
 * MLV_load_xml : 
 *
 * -----------------------------------------------------------------------------
 * MLV_get_string_value_from_xml : 
 *
 * -----------------------------------------------------------------------------
 * MLV_get_integer_value_from_xml : 
 *
 * -----------------------------------------------------------------------------
 * MLV_get_double_value_from_xml : 
 *
 * -----------------------------------------------------------------------------
 * MLV_get_number_of_objects_from_xml : 
 *
 * -----------------------------------------------------------------------------
 * MLV_free_xml : 
 *
 * -----------------------------------------------------------------------------
 *
 *
 */

#include  <MLV/MLV_all.h>
#include  <stdlib.h>

//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[] ){

	int annee;
	MLV_Xml* config;
	char* text;
	double reel;
	int nb_copains,i;	

	//
	// On charge en mémoire le fichier XML contenant toutes les informations
	// nécessaires au fonctionnement du programme.
	//	
	config = MLV_load_xml( "informations.xml" );


	//
	// On récupère puis on affiche le texte contenu dans l'élément 
	// informations/nom_programme
	//
	if(
		MLV_get_string_value_from_xml(
			config, &(text), "/informations/nom_programme"
		)
	){
		fprintf( stderr, "Le fichier XML n'est pas valide, l'élément /informations/nom_programme est manquant.\n" );
		exit(1);
	}

	printf("Titre : %s\n", text);
	free(text);

	
	//
	// On récupère puis on affiche l'entier contenu dans l'élément 
	// informations/anne_production
	//
	if(
		MLV_get_integer_value_from_xml(
			config, &(annee), "/informations/annee_production"
		)
	){
		fprintf( stderr, "Le fichier XML n'est pas valide, l'élément /informations/annee_production est manquant ou ne contient pas d'entier.\n" );
		exit(1);
	};

	printf("Annee de production : %d \n", annee);

	
	//
	// On récupère puis on affiche le réél contenu dans l'élément 
	// informations/reel_prefere
	//
	if(
		MLV_get_double_value_from_xml(
			config, &(reel), "/informations/reel_prefere"
		)
	){
		fprintf( stderr, "Le fichier XML n'est pas valide, l'élément /informations/reel_prefere est manquant ou ne contient pas de réel.\n" );
		exit(1);
	}

	printf("Mon réel préféré : %f \n", reel);


	// 
	// On affiche les copines.
	//
	printf("Mes copines sont : \n");
	nb_copains = MLV_get_number_of_objects_from_xml( 
		config, "/informations/amis/ami[@sexe='femme']"
	);
	for( i = 0; i< nb_copains; i++ ){
		if(
			MLV_get_string_value_from_xml(
				config, &(text), "/informations/amis/ami[@sexe='femme'][%d]",
				i+1
			)
		){
			fprintf( stderr, "Le fichier XML n'est pas valide, l'élément /informations/amis/ami[@sexe='femme'][%d] est manquant.\n", i+1 );
			exit(1);
		}
		printf("    - %s \n", text);
		free( text );
	}


	//
	// On libère l'espace alloué pour le fichier xml.
	//
	MLV_free_xml( config );

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
