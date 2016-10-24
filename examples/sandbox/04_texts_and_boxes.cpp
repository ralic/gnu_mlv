#include <MLV/experimental/window.hpp>


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main(int argc, char *argv[]){
	//
	// Déclaration et initialisation de la variable qui codera
	// la distance entre deux lignes dans un texte
	//
	int taille_interlinge = 9;

	//
	// Créé et affiche la fenêtre
	//
	mlv::window_t window(
		"beginner - 4 - texts and boxes", "texts and boxes", 640, 480 
	);

	//
	// Affiche du texte sans boîte
	//
	window.draw_text(
		mlv::point_t(10, 10), 
		"Simple texte. Avec draw_text() vous ne devez pas utiliser de retour "
		"à la ligne.",
		mlv::color::magenta
	);

	//
	// Affiche le contenu des variables. 
	//
	// Le format utilisé par la chaîne de 
	// caractère est le même que celui de printf de stdio.h.
	// On rapelle que le .2 du %f signifie que l'on affiche que les 2 premiers
	// chiffres après la virgurle du réel 'reel'.
	// Dans MLV, ce mécanisme existe dans toute les fonctions qui travaille 
	// avec une une chaîne de caractère. :)
	// Il suffit d'ajouter les variables à insérer dans le texte à la fin de la
	// fonction.
	//
	int entier = 42;
	double reel = 3.14;
	std::string texte = "entier = " + mlv::to_string(entier) + ", reel = " +
		mlv::to_string(reel);
	
	window.draw_text( mlv::point_t(10, 50), texte, mlv::color::magenta );

	//
	// Affiche du texte dans une boîte dont la taille s'adapte au texte
	// Le texte est justifié au centre dans la boîte
	//
	window.draw_text_box(
		mlv::box::text_t(
			mlv::point_t(10,100),
			"Exemple de boîte dont le contour\ns'adapte\nà la taille du texte.",
			taille_interlinge,
			mlv::color::red, mlv::color::green, mlv::color::black,
			mlv::text::center
		)
	);

	//
	// Affiche du texte dans une boîte dont la taille s'adapte au texte
	// Le texte est justifié à gauche dans la boîte
	//
	window.draw_text_box(
		mlv::box::text_t(
			mlv::point_t(10,190),
			"Même chose,\nmais le texte\nest justifié à gauche\nde la fenêtre.",
			taille_interlinge,
			mlv::color::red, mlv::color::green, mlv::color::black,
			mlv::text::left
		)
	);

	//
	// Affiche du texte dans une boîte de taille fixe.
	// Le texte est justifié à gauche, horizontalement et verticalement
	// centré.
	//
	window.draw_text_box(
		mlv::box::text_t(
			mlv::point_t(10,310),
			600, 150,
			"Cette fois-ci,\nla taille de la boîte ne correspond pas à "
			"l'espace couvert par le texte.\nLa boîte est ici plus grande.",
			taille_interlinge,
			mlv::color::red, mlv::color::green, mlv::color::black,
			mlv::text::left,
			mlv::text::horizontal_center, mlv::text::vertical_center
		)
	);

	//
	// Met à jour l'affichage de la fenêtre.
	//
	window.update();

	//
	// Attend 15 seconde avant la fin du programme.
	//
	window.wait_seconds( 15 );

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
