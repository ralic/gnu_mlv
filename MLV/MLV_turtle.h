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
 * \file MLV_turtle.h
 *
 * \author Adrien Boussicault
 *
 * \brief Ce fichier définit les prototypes des fonctions permettant de 
 *        manipuler des tortues fonctionnant comme les tortues de langage Logo.
 */

#ifndef __MLV__MLV_TURTLE_H__
#define __MLV__MLV_TURTLE_H__

#include "MLV_color.h"
#include "MLV_image.h"

#ifdef __cplusplus
extern "C" {
#endif

//
//  TODO : Ecrire la documentiation des fonctions
//

/** \~french
 * \brief La tortue Leonardo utilise désormais les angles en radian.
 *
 * Maienant les ordres reçus par la tortue seront en radian.
 * L'angle courant de la tortue est converti en radian.
 */
void MLV_leonardo_radian();

/** \~french
 * \brief La tortue Leonardo utilise désormais les angles en degrés.
 *
 * Maienant les ordres reçus par la tortue seront en degrés.
 * L'angle courant de la tortue est converti en degrés.
 */
void MLV_leonardo_degree();

/** \~french
 * \brief La tortue Leonardo avance d'un nombre de pixel donnée en paramètre.
 *
 * \param distance La distance en pixel à parcourir.
 */
void MLV_leonardo_forward( float distance );

/** \~french
 * \brief La tortue Leonardo tourne à droite d'un angle donné en paramètre.
 * 
 * L'angle passé en paramètre doit être en degré par défault.
 * Vous pouvez donner des radian, si vous avez changé le format des
 * angles utilisé par la tortue Leonardo en utilsant la fonction :
 * MLV_lonardo_radian().
 *
 * \param angle L'angle de la rotation (en degré par default).
 */
void MLV_leonardo_right( double angle );

/** \~french
 * \brief La tortue Leonardo tourne à gauche d'un angle donné en paramètre.
 * 
 * L'angle passé en paramètre doit être en degré par défault.
 * Vous pouvez donner des radian, si vous avez changé le format des
 * angles utilisé par la tortue Leonardo en utilsant la fonction :
 * MLV_lonardo_radian().
 *
 * \param angle L'angle de la rotation (en degré par default).
 */
void MLV_leonardo_left( double angle );

/** \~french
 * \brief La tortue Leonardo se déplace à la position passé en paramètre, 
 *        sans changer son orientation.
 *
 * Nous rapellons que l'origine est situé en haut à gauche de l'écran, que l
 * m'axe des x est orienté vers la gauche et l'axe des y vers le bas.
 * 
 * \param x La position en X.
 * \param y La position en Y.
 */
void MLV_leonardo_go_to( int x, int y );

/** \~french
 * \brief La tortue Leonardo s'oriente vers la direction donné en parmètre.
 *
 * La direction est codé à l'aide d'un angle entre le vecteur des axes des x
 * et la vecteur directeur de la tortue.
 *
 * Nous rapellons que l'origine est situé en haut à gauche de l'écran, que l
 * m'axe des x est orienté vers la gauche et l'axe des y vers le bas.
 * Ainsi, un angle positif corresond à une rotation dans le sens des 
 * aiguilles d'une montre.
 *
 * Si le pinceau est posé, un trait apparait.
 * 
 * \param angle La direction, codée par un angle entre l'axe des x et la direction.
 */
void MLV_leonardo_orient_to( double angle );

/** \~french
 * \brief Change la couleur du pinceau de la tortue Leonardo.
 *
 * \param color La couleur du pinceau.
 */
void MLV_leonardo_color( MLV_Color color );

/** \~french
 * \brief La tortue Leonardo pose le pinceau et écrit.
 *
 * Si le booléen write est vrai (!=0), alors le pinceau est posé et la tortue 
 * écrit.
 * Sinon le pinceau est relevé et la tortue n'écrit pas.
 *
 * Au moment où le pinceau est posée un point apparait.
 * 
 * \param write Un booléen.
 */
void MLV_leonardo_write( int write );

/** \~french
 * \brief Renvoie la coordonée en X de la tortue Leonardo.
 *
 * \return Un coordonée en X
 */
int MLV_leonardo_X_coordinate();

/** \~french
 * \brief Renvoie la coordonée en Y de la tortuei Leonardo.
 *
 * \return Un coordonée en Y
 */
int MLV_leonardo_Y_coordinate();

/** \~french
 * \brief Renvoie l'orientation de la tortue Leonardo.
 *
 * Par défault l'angle est en degrés à moins que le format de l'angle ait été
 * moifié à l'aide de la fonction MLV_leonardo_radian().
 *
 * \return Un angle
 */
double MLV_leonardo_orientation();

/** \~french
 * \brief Tourne la tortue Leonardo pour qu'elle regarde vers le point passé en 
 *        paramètre.
 *
 * \param x La coordonée X du point
 * \param y La coordonée Y du point
 */
void MLV_leonardo_point_to( int x, int y );

/** \~french
 * \brief Modifie la vitesse de la tortue Leonardo.
 *
 * Après chaque déplacement (rotation et translation) la tortue attends en 
 * mettant en attente le programme d'un nombre de milisedonde donné en paramètre
 * de cette fonction.
 * 
 * \param time Le nombre de milisecondes que le programme attends entre chaque
 *        déplacement.
 */
void MLV_leonardo_speed( int time );

/** \~french
 * \brief Demmande à la tortue Leonardo de mettre à jour l'affichage à chaque 
 *        déacement.
 *
 * Après chaque déplacement (rotation et translation) la tortue met à jour
 * l'affichage si le paramère de cette donction est positioné à vrai.
 * 
 * \param yes Un booléen.
 */
void MLV_leonardo_should_update_window( int yes );

/** \~french 
 * \brief Définit le type d'une tortue.
 *
 * Une tortue est un entité informatique qui permet de dessiner sur une image
 * en se déplacant, à l'aide d'ordre simple, comme avancer, tourner, etc ...
 */
typedef struct _MLV_Turtle MLV_Turtle;

/** \~french
 * \brief Créer une tortue qui dessine sur la fenêtre d'affichage.
 *
 * \param turtle Une tortue.
 */
MLV_Turtle* MLV_create_turtle();

/** \~french
 * \brief Libère la mémoire de la tortue.
 *
 * La mémoire associé à l'image sur laquelle la tortue dessine, n'est pas 
 * libérée.
 *
 * \param turtle Une tortue.
 */
void MLV_free_turtle( MLV_Turtle* turtle );

/** \~french
 * \brief Attache la tortue sur une image passé en paramètre.
 *
 * Par défault, la tortue est attachée à l'image de la fenêtre d'affichage, 
 * celle qui est affichée lorsque l'on utilise la fonction MLV_update_window().
 *
 * Si vous attachez la tortue à une autre image, alors la tortue dessinera
 * uniquement sur l'image qui vient d'être attachée et sur aucune autre image.
 *
 * Si vous passez NULL au paramètre de cette fonction, alors la tortue 
 * s'attache de nouveau à l'image par défault, c'est à dira à l'image de la 
 * fenête d'affichage.
 *
 * La tortue ne devient pas propriétaire de l'image passée en paramètre.
 * Elle ne libère donc pas la mémoire associée à l'image lorsque la mémoire de 
 * la tortue est libérée en utilisant la fonction MLV_free_turtle().
 *
 * \param turtle Une tortue.
 * \param image Une image.
 */
void MLV_turtle_attach_on_image( MLV_Turtle* turtle, MLV_Image* image );

/** \~french
 * \brief La tortue passée en paramètre utilise désormais les angles en radian.
 *
 * Maienant les ordres reçus par la tortue seront en radian.
 * L'angle courant de la tortue est converti en radian.
 *
 * \param turtle Une tortue.
 */
void MLV_turtle_radian( MLV_Turtle* turtle );

/** \~french
 * \brief La tortue passée en paramètre utilise désormais les angles en degrés.
 *
 * Maienant les ordres reçus par la tortue seront en degrés.
 * L'angle courant de la tortue est converti en degrés.
 *
 * \param turtle Une tortue.
 */
void MLV_turtle_degree( MLV_Turtle* turtle );

/** \~french
 * \brief La tortue avance d'un nombre de pixel donnée en paramètre.
 *
 * \param turtle Une tortue.
 * \param distance La distance en pixel à parcourir.
 */
void MLV_turtle_forward( MLV_Turtle* turtle, float distance );

/** \~french
 * \brief La tortue à droite d'un angle donné en paramètre.
 * 
 * L'angle passé en paramètre doit être en degré par défault.
 * Vous pouvez donner des radian, si vous avez changé le format des
 * angles utilisé par la tortue en utilsant la fonction :
 * MLV_lonardo_radian().
 *
 * \param turtle Une tortue.
 * \param angle L'angle de la rotation (en degré par default).
 */
void MLV_turtle_right( MLV_Turtle* turtle, double angle );

/** \~french
 * \brief La tortue tourne à gauche d'un angle donné en paramètre.
 * 
 * L'angle passé en paramètre doit être en degré par défault.
 * Vous pouvez donner des radian, si vous avez changé le format des
 * angles utilisé par la tortue en utilsant la fonction :
 * MLV_lonardo_radian().
 *
 * \param turtle Une tortue.
 * \param angle L'angle de la rotation (en degré par default).
 */
void MLV_turtle_left( MLV_Turtle* turtle, double angle );

/** \~french
 * \brief La tortue se déplace à la position passé en paramètre, sans changer 
 *        son orientation.
 *
 * Nous rapellons que l'origine est situé en haut à gauche de l'écran, que l
 * m'axe des x est orienté vers la gauche et l'axe des y vers le bas.
 * 
 * \param turtle Une tortue.
 * \param x La position en X.
 * \param y La position en Y.
 */
void MLV_turtle_go_to( MLV_Turtle* turtle, int x, int y );

/** \~french
 * \brief La tortue s'oriente vers la direction donné en parmètre.
 *
 * La direction est codé à l'aide d'un angle entre le vecteur des axes des x
 * et la vecteur directeur de la tortue.
 *
 * Nous rapellons que l'origine est situé en haut à gauche de l'écran, que l
 * m'axe des x est orienté vers la gauche et l'axe des y vers le bas.
 * Ainsi, un angle positif corresond à une rotation dans le sens des 
 * aiguilles d'une montre.
 *
 * \param turtle Une tortue.
 * \param angle La direction, codée par un angle entre l'axe des x et la direction.
 */
void MLV_turtle_orient_to( MLV_Turtle* turtle, double angle );

/** \~french
 * \brief Change la couleur du pinceau de la tortue passée en paramètre.
 *
 * \param turtle Une tortue.
 * \param color La couleur du pinceau.
 */
void MLV_turtle_color( MLV_Turtle* turtle, MLV_Color color );

/** \~french
 * \brief La tortue pose le pinceau et écrit.
 *
 * Si le booléen write est vrai (!=0), alors le pinceau est posé et la tortue 
 * écrit.
 * Sinon le pinceau est relevé et la tortue n'écrit pas.
 *
 * Au moment où le pinceau est posée un point apparait.
 * 
 * \param turtle Une tortue.
 * \param write Un booléen.
 */
void MLV_turtle_write( MLV_Turtle* turtle, int write );

/** \~french
 * \brief Tourne la tortue pour qu'elle regarde vers le point passé en 
 *        paramètre.
 *
 * \param turtle Une tortue.
 * \param x La coordonée X du point
 * \param y La coordonée Y du point
 */
void MLV_turtle_point_to( MLV_Turtle* turtle, int x, int y );

/** \~french
 * \brief Renvoie la coordonée en X de la tortue.
 *
 * \param turtle Une tortue.
 * \return Un coordonée en X
 */
int MLV_turtle_X_coordinate( MLV_Turtle* turtle );

/** \~french
 * \brief Renvoie la coordonée en Y de la tortue.
 *
 * \param turtle Une tortue.
 * \return Un coordonée en Y
 */
int MLV_turtle_Y_coordinate( MLV_Turtle* turtle );

/** \~french
 * \brief Renvoie l'orientation de la tortue.
 *
 * Par défault l'angle est en degrés à moins que le format de l'angle ait été
 * moifié à l'aide de la fonction MLV_turtle_radian().
 *
 * \param turtle Une tortue.
 * \return Un angle
 */
double MLV_turtle_orientation( MLV_Turtle* turtle );

#ifdef __cplusplus
}
#endif

#endif
