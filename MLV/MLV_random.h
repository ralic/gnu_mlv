/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2010,2011,2012 Adrien Boussicault, Marc Zipstein
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
 * \file MLV_random.h
 *
 * \author Adrien Boussicault
 * \author Marc Zipstein
 *
 * \brief Ce fichier définit tous les prototypes des fonctions concernant
 *        la manipulation des nombres aléatoires.
 * 
 */

#ifndef __MLV__MLV_RANDOM_H__
#define __MLV__MLV_RANDOM_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \~french
 *
 * \brief Initialise la graine du générateur de nombre interne.
 *
 * Par défaut, la graine de générateur de nombre est automatiquement 
 * initialisé, à des valeurs différentes à chaque execution du programme.
 *
 * Utilisez cette fonction si vous voulez que le générateur de nombre
 * aléatoire utilise une graine particulière (pour faire des tests 
 * reproductibles d'une execution sur l'autre).
 * Dans le cas contraire, vous n'avez pas besoin d'utiliser cette fonction.
 *
 * \param seed La graine (entier sur 32 bits).
 *
 */
void MLV_set_seed( int32_t seed );

/** \~french 
 * \brief Renvoie 0 ou 1 aléatoirement.
 *
 * \return 0 ou 1 aléatoirement.
 */
int MLV_get_random_boolean();

/** \~french 
 * \brief Renvoie un entier aléatoire choisi dans un intervalle donné en 
 *        paramètre.
 *
 * \param begin Borne inférieur de l'intervalle ( inclusif )
 * \param end Borne supérieur de l'intervalle ( inclusif )
 * \return  Un entier aléatoire choisi dans l'intervalle [begin, end].
 */
int MLV_get_random_integer(int begin, int end);

/** \~french 
 * \brief Renvoie un réel aléatoire choisi dans un intervalle donné en 
 *        paramètre.
 *
 * \param begin Borne inférieur de l'intervalle ( inclusif )
 * \param end Borne supérieur de l'intervalle ( inclusif )
 * \return Un réel aléatoire choisi dans l'intervalle [begin, end].
 */
double MLV_get_random_double(double begin, double end);

#ifdef __cplusplus
}
#endif

#endif
