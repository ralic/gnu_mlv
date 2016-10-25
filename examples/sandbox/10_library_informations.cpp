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
	// la taille entre deux lignes dans un texte
	//
	int taille_interlinge = 9;

	//
	// Créé et affiche la fenêtre
	//
	mlv::window_t window(
		"beginner - 10 - library informations", "library informations", 640, 480
	);

	std::string text = std::string("") +
		"Nom de la bibliothèque : " + MLV_get_package_name() +
		"     Depôt : " + MLV_get_repository( ) +
		"\nVersion : " + MLV_get_version() +
		"  ( révision : " + MLV_get_revision_of_revision_control_software( ) +
		"  )\nLicence : " + MLV_get_licence() +
		"\nAddresse internet où se trouve le code source de la bibliothèque :\n"
		"    " + MLV_get_web_distribution() +
		"\n\nCette bibliothèque est distibuée sous le terme de la licence " +
		MLV_get_licence() +
		". Vous trouverez une\n"
		"copie de cette licence dans le fichier gpl.txt du répertoire courant.\n"
		"\nLa licence " + MLV_get_licence() +
		"  garantit à l'utilisateur les droits suivants :\n"
		"    1. La liberté d'exécuter le logiciel, pour n'importe quel usage ;\n"
		"    2. La liberté d'étudier le fonctionnement d'un programme et de l'adapter \n"
		"        à ses besoins, ce qui passe par l'accès aux codes sources ;\n"
		"    3. La liberté de redistribuer des copies ;\n"
		"    4. La liberté de rendre publiques des versions modifiées pour en faire \n"
		"       bénéficier la communauté.\n\n"
		"La licence GPL impose aussi quelques devoirs. "
		"Par exemple, si vous distribuez un\n "
		"programme utilisant MLV, vous devez le faire sous une licence compatible GPL."
	;

	//
	// Affiche quelques informations concernant la librairie MLV
	//
	window.draw_text_box(
		mlv::box::text_t(
			mlv::point_t(10,10), text, taille_interlinge,
			mlv::color::black, mlv::color::green, mlv::color::black,
			mlv::text::left
		)
	);

	//
	// Met à jour de l'affichage
	//
	window.update();
	
	//
	// Attends que l'utilisateur appuye sur la touche echap pour quitter.
	//
	mlv::event::key_t key;
	while( key.sym != MLV_KEYBOARD_ESCAPE ){
		window.wait_keyboard(key);
	}

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
