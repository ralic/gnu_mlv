/**
 *
 * Ce programme affiche différentes informations de temps.
 *
 * Pour cela le programme  utilise les fonctions suivantes : 
 *
 *------------------------------------------------------------------------------
 * MLV_get_time : 
 *
 *------------------------------------------------------------------------------
 * MLV_get_date : 
 *
 *------------------------------------------------------------------------------
 */

#include <MLV/MLV_all.h>
#include <stdio.h>


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[] ){
	int elapsed_time;
	int seconds, minutes, hours, day, month, year, day_of_the_week;
	const char* days[7] ={ 
		"Dimanche", "Lundi", "Mardi", "Mercredi","Jeudi", "Vendredi", "Samedi"
	};
	const char* months[12] ={ 
		"Janvier", "Févier", "Mars", "Avril","Mai", "Juin", "Juillet",
		"Août", "Septembre", "Octobre", "Novembre", "Décembre"
	};

	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window( "medium - 7 - time", "time", 640, 480 );

	while( 1 ){

		MLV_clear_window( MLV_COLOR_BLACK );

		//
		// On récupère le temps écoulé depuis le debut de l'éxécution du 
		// programme
		//
		elapsed_time =  MLV_get_time();
		//
		// On affiche l'infomration obtenue
		//
		MLV_draw_text(
			10, 120, 
			"Temps écoulé depuis le debut du programme : %d ms",
			MLV_COLOR_GREEN, elapsed_time
		);


		//
		// On récupère la date d'aujourd'hui et l'heure courante
		//
		MLV_get_date(
			&seconds, &minutes, &hours,
			&day, &month, &year,
			&day_of_the_week
		);
		//
		// On affiche les jours
		//
		MLV_draw_text(
			10, 240, 
			"Date :  %s, %.2d %s %d",
			MLV_COLOR_GREEN,
			days[day_of_the_week], day, months[month], year			
		);
		//
		// On affiche l'heure
		//
		MLV_draw_text(
			10, 260, 
			"Heure :  %d h %.2d : %.2d",
			MLV_COLOR_GREEN,
			hours, minutes, seconds			
		);

		//
		// On met à jour l'affichage
		//		
		MLV_actualise_window();

	}

	//
	// Ferme la fenêtre
	//
	MLV_free_window();

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
