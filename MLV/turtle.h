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

/** \~french 
 * \file turtle.h
 *
 * \author Adrien Boussicault
 *
 * \brief Ce fichier définit les prototypes des fonctions permettant de 
 *        manipuler une tortue.
 */

#ifndef __MLV__TURTLE_H__
#define __MLV__TURTLE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _MLV_Leonardo_turtle MLV_Leonardo_turtle;

void init_leonardo_turtle();
void free_leonardo_turtle();

#ifdef __cplusplus
}
#endif

#endif
