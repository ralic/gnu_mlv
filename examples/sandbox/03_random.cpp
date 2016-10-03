#include <MLV/experimental/window.hpp>
#include <iostream>


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main(int argc, char *argv[]){
	//
	// Déclaration des variables qui contiendront les
	// nombres aléatoires qui seront engendrés
	//
	int resultat_i, resultat_b;
	double resultat_d;

	//
	// Récupère et affiche un entier aléatoire
	//
	resultat_i = mlv::random_integer(3,100);
	std::cout << "Entier aléatoire entre 3 et 100 : " 
		<< resultat_i << std::endl;

	//
	// Récupère et affiche un réel aléatoire
	//
	resultat_d = mlv::random_double( 3.0, 100.0 );
	std::cout << "Réel aléatoire entre 3.0 et 100.0 : "
		<< resultat_d << std::endl;

	//
	// Récupère et affiche un booléen aléatoire
	//
	resultat_b = mlv::random_boolean();
	std::cout << "Boolean aléatoire : " << resultat_b
		<< std::endl;

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
