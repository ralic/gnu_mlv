/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2010,2011,2012 Adrien Boussicault, Marc Zipstein
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
 * \file MLV_event.h
 *
 * \author Adrien Boussicault
 * \author Marc Zipstein
 * 
 * \brief Ce fichier définit les prototypes des fonctions permettant d'utiliser
 *        les évènements dans la bibliothèque MLV.
 */

#ifndef __MLV__MLV_EVENT_H__
#define __MLV__MLV_EVENT_H__

#include "MLV_device_with_buttons.h"
#include "MLV_keyboard.h"
#include "MLV_mouse.h"
#include "MLV_input_box.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \~french 
 * \brief Énumère les différents types d'évènement de la bibliothèque MLV.
 */
typedef enum {
	MLV_NONE = 0, /**< \~french Aucun évènement */
	MLV_KEY = 1, /**< \~french  Evnènement provenant du clavier */
	MLV_INPUT_BOX = 2, /**< \~french Évènement provenant de la validation d'un texte dans 
	                 *   une boîte de saisie. */
	MLV_MOUSE_BUTTON = 3, /**< \~french  Évènement provenant d'un clique de souris. */
	MLV_MOUSE_MOTION = 4 /**< \~french  Évènement provenant du déplacement de la souris.*/
} MLV_Event;


 /** \~french 
 * \brief Cette fonction récupère un évènement dans la file d'attente, remplit 
 *        en fonction de l'évènement récupéré une partie des paramètres de la 
 *        fonction et renvoie un entier codant le type de l'évènement qui a été
 *        récupéré.
 *
 * Le type des évènements est défini par :
 *
 *     MLV_Event
 *
 * et peut valoir les valeurs suivantes:
 *
 *     Valeur ...........  Signification
 *
 *     ----------------------------------
 *
 *     MLV_NONE .......... Aucun évènement récupéré
 *
 *     MLV_KEY ........... Une touche du clavier a été appuyée ou
 *                         relachée.
 *
 *     MLV_INPUT_BOX ..... L'utilisateur a écrit une chaîne de
 *                         caractères et validé cette chaîne par
 *                         la touche entrée.
 *
 *     MLV_MOUSE_BUTTON .. Un des boutons de la souris a été
 *                         appuyé.
 *
 *     MLV_MOUS_MOTION ... La souris a été déplacée.
 *
 *
 *
 *  Voici un tableau qui donne les champs modifiés en fonction 
 *  de l'évènement qui a été récupéré.
 *
 *     Type Évènement .... Paramètres modifiés
 *
 *     ---------------------------------------
 *
 *     MLV_NONE .......... AUCUN
 *
 *     MLV_KEY ........... key_sym, key_mod, state
 *
 *     MLV_INPUT_BOX ..... texte, input_box
 *
 *     MLV_MOUSE_BUTTON .. mouse_x, mouse_y, mouse_button, state
 *
 *     MLV_MOUSE_MOTION .. mouse_x, mouse_y
 *
 *
 *  L'utilisateur n'est pas obligé d'utiliser un champs s'il
 *  n'en a pas l'utilité. Dans ce cas, il peut mettre la valeur
 *  NULL. Le champs est alors ignoré.
 *
 * \bug Il est possible que la récuperation du caractère unicode sous Windows
 *      ne fonctionne pas bien. En effet, aucun code de portage spécifique n'a été 
 *      fait à ce sujet.
 *
 * \bug Sous WINDOWS, le clavier est configuré en "qwerty".
 *
 * \return La fonction renvoie un entier codant le type de l'évènement qui a 
 *         été récupéré.
 *
 * \param key_sym Code de la touche qui a été appuyée ou relachée. La valeur de 
 *                ce champs est définie par l'énumération : MLV_Keyboard_button.
 * \param key_mod Mode dans lequel se trouve le clavier lorsqu'une touche est 
 *                appuyée ou relachée. La valeur de ce champs est définie par 
 *                l'énumération : MLV_Keyboard_modifier.
 * \param unicode Caractère codé en unicode de la lettre obtenue en combinant 
 *                le code et le mode précédent
 * \param texte Texte récupéré par la boîte de saisie. L'allocation est 
 *              affectée par la fonction elle-même. La désallocation est à 
 *              la charge de l'utilisateur.
 * \param input_box La boîte de saisie qui a récupérée le texte
 * \param mouse_x Coordonnée en X de la position de la souris
 * \param mouse_y Coordonnée en Y de la position de la souris
 * \param mouse_button Bouton de la souris qui a été appuyé ou relaché.
 *                     Ce champs est défini par l'énumération MLV_Mouse_button.
 * \param state Etat de la touche concernée par l'évènement. La valeur de ce 
 *              champs est défini par l'énumération: MLV_Button_state.
 */
MLV_Event MLV_get_event( 
	MLV_Keyboard_button* key_sym, MLV_Keyboard_modifier* key_mod, int* unicode, 
	char** texte, MLV_Input_box** input_box,
	int* mouse_x, int* mouse_y, MLV_Mouse_button* mouse_button,
	MLV_Button_state* state
);



 /** \~french 
 * \brief Cette fonction suspends l'éxecution du programme jusqu'à ce qu'un 
 *        évènement apparaît dans la file d'attente. Lorsqu'un nouvel 
 *        évènement apparaît, la fonction
 *        - remplit ses paramètres et renvoie un entier codant le type de 
 *          l'évènement qui a été récupéré, si les paramètres passés en 
 *          argument concernent l'évènement récupéré.
 *        - se rendort en l'attente d'un nouvel évènement, dans le cas 
 *          contraire.
 *
 * Pour plus d'informations sur les différents types d'évènements et leurs 
 * liens avec les paramètres de la fonction, veuillez consulter la 
 * documentation de la fonction MLV_get_event().
 *
 * L'utilisateur n'est pas obligé d'utiliser un champs s'il
 * n'en a pas l'utilité. Dans ce cas, il peut mettre la valeur
 * NULL et le paramètre est ignoré.
 *
 * \bug Voir les bugs de la fonction MLV_get_event().
 *
 * \param key_sym Code de la touche qui a été appuyée ou relachée. La valeur de
 *                ce champs est définie par l'énumération : MLV_Keyboard_button.
 * \param key_mod Mode dans lequel se trouve le clavier lorsqu'une touche est 
 *                appuyée ou relachée. La valeur de ce champs est définie par 
 *                l'énumération : MLV_Keyboard_modifier.
 * \param unicode Caractère codé en unicode de la lettre obtenue en combinant 
 *                le code et le mode précédent
 * \param texte Texte récupéré par la boîte de saisie. L'allocation est affecté par la
 *                    la fonction elle même. La désallocation est à la charge de
 *                    l'utilisateur.
 * \param input_box La boîte de saisie qui a récupérée le texte
 * \param mouse_x Coordonnée en X de la position de la souris
 * \param mouse_y Coordonnée en Y de la position de la souris
 * \param mouse_button Bouton de la souris qui a été appuyé ou relaché. 
 *                     Ce champs est défini par l'énumération MLV_Mouse_button.
 * \param state Etat de la touche concernée par l'évènement. La valeur de ce 
 *              champs est défini par l'énumération: MLV_Button_state.
 * 
 * \return La fonction renvoie un entier codant le type de l'évènement qui 
 *         a été récupéré.
 */
MLV_Event MLV_wait_event( 
	MLV_Keyboard_button* key_sym, MLV_Keyboard_modifier* key_mod, int* unicode,
	char** texte, MLV_Input_box** input_box,
	int* mouse_x, int* mouse_y, MLV_Mouse_button* mouse_button,
	MLV_Button_state* state
);


 /** \~french
 * \brief Cette fonction suspends l'éxecution du programme jusqu'à ce qu'un 
 *        évènement apparaît dans la file d'attente ou jusqu'à ce qu'un certain 
 *        nombre de secondes se soient écoulées. 
 *        Si le temps s'est complètement écoulé, la fonction renvoie MLV_NONE.
 *        Si un nouvel évènement apparaît et que les paramètres passés en arguments 
 *        sont en rapport avec l'évènement récupéré, alors la fonction 
 *        remplit les paramètres et renvoie un entier codant le type de 
 *        l'évènement qui a été récupéré.
 *        Si un nouvel évènement apparaît et qu'il n'est pas en rapport 
 *        avec les paramètres de la fonction, alors il se rendort dans 
 *        l'attente d'un nouvel évènement ou de la fin du temps.
 *
 * Pour plus d'informations sur les différents types d'évènements et leurs 
 * liens avec les paramètres de la fonction, veuillez consulter la 
 * documentation de la fonction MLV_get_event().
 *
 * L'utilisateur n'est pas obligé d'utiliser un champs s'il
 * n'en a pas l'utilité. Dans ce cas, il peut mettre la valeur
 * NULL. Le champs est alors ignoré.
 *
 * \bug Voir les bugs de la fonction MLV_get_event().
 *
 * \param key_sym Code de la touche qui a été appuyée ou relachée. La valeur de 
 *                ce champs est définie par l'énumération : MLV_Keyboard_button.
 * \param key_mod Mode dans lequel se trouve le clavier lorsqu'une touche est 
 *                appuyée ou relachée. La valeur de ce champs est définie par 
 *                l'énumération : MLV_Keyboard_modifier.
 * \param unicode Caractère codé en unicode de la lettre obtenue en combinant 
 *                le code et le mode précédent
 * \param texte Texte récupéré par la boîte de saisie. L'allocation est affecté par la
 *                    la fonction elle même. La désallocation est à la charge de
 *                    l'utilisateur.
 * \param input_box La boîte de saisie qui a récupérée le texte
 * \param mouse_x Coordonnée en X de la position de la souris
 * \param mouse_y Coordonnée en Y de la position de la souris
 * \param mouse_button Bouton de la souris qui a été appuyé ou relaché. 
 *                     Ce champs est défini par l'énumération MLV_Mouse_button.
 * \param state Etat de la touche concernée par l'évènement. La valeur de ce 
 *              champs est défini par l'énumération: MLV_Button_state.
 * \param seconds Nombre de secondes à attendre avant de terminer l'execution de
 *                la fonction en renvoyant MLV_NONE.
 * \return La fonction renvoie un entier codant le type de l'évènement qui 
 *         a été récupéré ou MLV_NONE si le temps s'est écoulé.
 */
MLV_Event MLV_wait_event_or_seconds( 
	MLV_Keyboard_button* key_sym, MLV_Keyboard_modifier* key_mod, int* unicode,
	char** texte, MLV_Input_box** input_box,
	int* mouse_x, int* mouse_y, MLV_Mouse_button* mouse_button,
	MLV_Button_state* state, int seconds
);

 /** \~french
 * \brief Cette fonction suspends l'éxecution du programme jusqu'à ce qu'un 
 *        évènement apparaît dans la file d'attente ou jusqu'à ce qu'un certain 
 *        nombre de millisecondes se soient écoulées. 
 *        Si le temps s'est complètement écoulé, la fonction renvoie MLV_NONE.
 *        Si un nouvel évènement apparaît et que les paramètres passés en arguments 
 *        sont en rapport avec l'évènement récupéré, alors la fonction 
 *        remplit les paramètres et renvoie un entier codant le type de 
 *        l'évènement qui a été récupéré.
 *        Si un nouvel évènement apparaît et qu'il n'est pas en rapport 
 *        avec les paramètres de la fonction, alors il se rendort dans 
 *        l'attente d'un nouvel évènement ou de la fin du temps.
 *
 * Pour plus d'informations sur les différents types d'évènements et leurs 
 * liens avec les paramètres de la fonction, veuillez consulter la 
 * documentation de la fonction MLV_get_event().
 *
 * L'utilisateur n'est pas obligé d'utiliser un champs s'il
 * n'en a pas l'utilité. Dans ce cas, il peut mettre la valeur
 * NULL. Le champs est alors ignoré.
 *
 * \bug Voir les bugs de la fonction MLV_get_event().
 *
 * \param key_sym Code de la touche qui a été appuyée ou relachée. La valeur de 
 *                ce champs est définie par l'énumération : MLV_Keyboard_button.
 * \param key_mod Mode dans lequel se trouve le clavier lorsqu'une touche est 
 *                appuyée ou relachée. La valeur de ce champs est définie par 
 *                l'énumération : MLV_Keyboard_modifier.
 * \param unicode Caractère codé en unicode de la lettre obtenue en combinant 
 *                le code et le mode précédent
 * \param texte Texte récupéré par la boîte de saisie. L'allocation est affecté par la
 *                    la fonction elle même. La désallocation est à la charge de
 *                    l'utilisateur.
 * \param input_box La boîte de saisie qui a récupérée le texte
 * \param mouse_x Coordonnée en X de la position de la souris
 * \param mouse_y Coordonnée en Y de la position de la souris
 * \param mouse_button Bouton de la souris qui a été appuyé ou relaché. 
 *                     Ce champs est défini par l'énumération MLV_Mouse_button.
 * \param state Etat de la touche concernée par l'évènement. La valeur de ce 
 *              champs est défini par l'énumération: MLV_Button_state.
 * \param milliseconds Nombre de millisecondes à attendre avant de terminer l'execution de
 *                la fonction en renvoyant MLV_NONE.
 * \return La fonction renvoie un entier codant le type de l'évènement qui 
 *         a été récupéré ou MLV_NONE si le temps s'est écoulé.
 */
MLV_Event MLV_wait_event_or_milliseconds( 
	MLV_Keyboard_button* key_sym, MLV_Keyboard_modifier* key_mod, int* unicode,
	char** texte, MLV_Input_box** input_box,
	int* mouse_x, int* mouse_y, MLV_Mouse_button* mouse_button,
	MLV_Button_state* state, int milliseconds
);



/** \~french 
 * \brief Cette fonction vide la file d'évènements.
 *
 */
void MLV_flush_event_queue();

/** \~french 
 * \brief Suspend l'exécution jusqu'à ce que l'utilisateur appuie sur une touche
 *        du clavier ou sur le bouton gauche de la souris.
 *
 * Cette fonction renvoie un entier codant le type de l'évènement qui a été 
 * récupéré ( clavier ou souris )
 *
 * Lorsque l'utilisateur appuie sur une touche, la fonction retourne trois 
 * valeurs ( sym, mod et unicode ) correspondant respectivement au code de la
 * touche, au mode dans lequel se trouve le clavier (majuscule etc ...) et au 
 * caractère unicode correspondnant obtenu en combinant le mode du clavier et le
 * code de la touche appuyée.
 *
 * Lorsque l'utilisateur appuie sur le bouton gauche de la souris, la fonction 
 * remplit les parametres correspondant aux coordonnées en X et Y de la position
 * de la souris sur l'écran.
 *
 * \bug Voir les bugs de la fonction MLV_get_event().
 *
 * \param sym Code de la touche qui a été appuyée ou relachée. La valeur de ce
 *            champs est définie par l'énumération : MLV_Keyboard_button.
 * \param mod Mode dans lequel se trouve le clavier lorsqu'une touche est
 *            appuyée ou relachée. La valeur de ce champs est définie par 
 *            l'énumération : MLV_Keyboard_modifier.
 * \param unicode Caractère codé en unicode de la lettre obtenue en combinant 
 *                le code et le mode précédent
 * \param mouse_x Coordonnée en X de la position de la souris
 * \param mouse_y Coordonnée en Y de la position de la souris
 * \return un entier codant le type de l'évènement qui a été récupéré ( MLV_KEY 
 *         ou MLV_MOUSE_BUTTON )
 */
MLV_Event MLV_wait_keyboard_or_mouse(
	MLV_Keyboard_button* sym, MLV_Keyboard_modifier* mod, int* unicode,
	int* mouse_x, int* mouse_y
);


/** \~french 
 * \brief Suspend l'exécution jusqu'à ce que l'utilisateur appuie sur une touche
 *        du clavier, sur le bouton gauche de la souris ou qu'un certain nombre
 *        de secondes passées en paramètres se soient écoulées.
 *
 * Cette fonction renvoie un entier codant le type de l'évènement qui a été 
 * récupéré ( clavier, souris ou aucun des deux ).
 *
 * Voir les fonctions MLV_wait_keyboard_seconds() et MLV_wait_mouse_seconds()
 * pour plus d'informations.
 *
 * \bug Voir les bugs de la fonction MLV_get_event().
 *
 * \param sym Code de la touche qui a été appuyée ou relachée. La valeur de ce 
 *        champs est définie par l'énumération : MLV_Keyboard_button.
 * \param mod Mode dans lequel se trouve le clavier lorsqu'une touche est 
 *            appuyée ou relachée. La valeur de ce champs est définie par 
 *            l'énumération : MLV_Keyboard_modifier.
 * \param unicode Caractère codé en unicode de la lettre obtenue en combinant le
 *                code et le mode précédent
 * \param mouse_x Coordonnée en X de la position de la souris
 * \param mouse_y Coordonnée en Y de la position de la souris
 * \param seconds Le nombre de seconde à attendre avant d'arrêter la fonction
 * \return un entier codant le type de l'évènement qui a été récupéré ( MLV_KEY 
 *         ou MLV_MOUSE_BUTTON ), ou MLV_NONE si le temps s'est écoulé.
 */
MLV_Event MLV_wait_keyboard_or_mouse_or_seconds(
	MLV_Keyboard_button* sym, MLV_Keyboard_modifier* mod, int* unicode,
	int* mouse_x, int* mouse_y,
	int seconds
);

/** \~french 
 *
 * \brief Suspend l'exécution jusqu'à ce que l'utilisateur clique sur le bouton
 *        gauche de la souris.
 *
 * Au moment où l'utilisateur clique, la fonction retourne les
 * coordonnées de la position de la souris dans la fenêtre.
 *
 * \param x Coordonnée en X de la position de la souris dans la fenêtre.
 * \param y Coordonnée en Y de la position de la souris dans la fenêtre.
 * \param milliseconds Le nombre de milliseconde à attendre.
 * \return un entier codant le type de l'évènement qui a été récupéré ( 
 *         MLV_MOUSE_BUTTON ), ou MLV_NONE si le temps s'est écoulé.
 */
MLV_Event MLV_wait_mouse_or_milliseconds(int *x, int *y, int milliseconds);

/** \~french 
 *
 * \brief Suspend l'exécution jusqu'à ce que l'utilisateur clique sur le bouton
 *        gauche de la souris où jusqu'à ce qu'un nombre de secondes, passé en 
 *        paramètres, se soient écoulées.
 *
 * Au moment où l'utilisateur clique, la fonction retourne les
 * coordonnées de la position de la souris dans la fenêtre.
 *
 * \param x Coordonnée en X de la position de la souris dans la fenêtre.
 * \param y Coordonnée en Y de la position de la souris dans la fenêtre.
 * \param seconds Le nombre de second à attendre avant de quitter la fonction.
 * \return un entier codant le type de l'évènement qui a été récupéré ( 
 *         MLV_MOUSE_BUTTON ), ou MLV_NONE si le temps s'est écoulé.
 */
MLV_Event MLV_wait_mouse_or_seconds(int *x, int *y, int seconds);

/** \~french 
 * \brief Suspend l'exécution jusqu'à ce que l'utilisateur appuie sur une touche
 *        du  clavier ou jusq'à ce q'un nombre de secondes passées en paramètres
 *        soient écoulées.
 * 
 * Pour plus d'informations sur le fonctionnement de cette fonction, veuillez 
 * vous reporter à la documentation de MLV_wait_keyboard().
 *
 * La fonction accepte des valeurs nulles pour les pointeurs sym, mod et 
 * unicode.
 * Dans ce cas la fonction ignore les champs en questions.
 *
 * \bug Voir les bugs de la fonction MLV_get_event().
 *
 * \param sym        Le code de la touche. 
 * \param mod        Le mode dans lequel se trouve le clavier.
 * \param unicode    Le caractère codé en unicode de la lettre obtenue en combinant
 *                   le code et le mode précédent.
 * \param seconds    Le nombre de secondes à attendre.
 * \return un entier codant le type de l'évènement qui a été récupéré ( MLV_KEY 
 *         ), ou MLV_NONE si le temps s'est écoulé.
 */
MLV_Event MLV_wait_keyboard_or_seconds(
	MLV_Keyboard_button* sym, MLV_Keyboard_modifier* mod, int* unicode, 
	int seconds
);

/** \~french 
 * \brief Suspend l'exécution jusqu'à ce que l'utilisateur appuie sur une touche
 *        du  clavier ou jusq'à ce q'un nombre de millisecondes passées en 
 *        paramètres soient écoulées.
 * 
 * Pour plus d'informations sur le fonctionnement de cette fonction, veuillez 
 * vous reporter à la documentation de MLV_wait_keyboard().
 *
 * La fonction accepte des valeurs nulles pour les pointeurs sym, mod et 
 * unicode.
 * Dans ce cas la fonction ignore les champs en questions.
 *
 * \bug Voir les bugs de la fonction MLV_get_event().
 *
 * \param sym        Le code de la touche. 
 * \param mod        Le mode dans lequel se trouve le clavier.
 * \param unicode    Le caractère codé en unicode de la lettre obtenue en combinant
 *                   le code et le mode précédent.
 * \param milliseconds    Le nombre de millisecondes à attendre.
 * \return un entier codant le type de l'évènement qui a été récupéré ( MLV_KEY 
 *         ), ou MLV_NONE si le temps s'est écoulé.
 */
MLV_Event MLV_wait_keyboard_or_milliseconds(
	MLV_Keyboard_button* sym, MLV_Keyboard_modifier* mod, int* unicode, 
	int milliseconds
);

/** \~french 
 * \brief Suspend l'exécution jusqu'à ce que l'utilisateur appuie sur une touche
 *        du clavier, sur le bouton gauche de la souris ou qu'un certain nombre
 *        de millisecondes passées en paramètres se soient écoulées.
 *
 * Cette fonction renvoie un entier codant le type de l'évènement qui a été 
 * récupéré ( clavier, souris ou aucun des deux ).
 *
 * Voir les fonctions MLV_wait_keyboard_milliseconds() et 
 * MLV_wait_mouse_milliseconds() pour plus d'informations.
 *
 * \bug Voir les bugs de la fonction MLV_get_event().
 *
 * \param sym Code de la touche qui a été appuyée ou relachée. La valeur de ce 
 *        champs est définie par l'énumération : MLV_Keyboard_button.
 * \param mod Mode dans lequel se trouve le clavier lorsqu'une touche est 
 *            appuyée ou relachée. La valeur de ce champs est définie par 
 *            l'énumération : MLV_Keyboard_modifier.
 * \param unicode Caractère codé en unicode de la lettre obtenue en combinant le
 *                code et le mode précédent
 * \param mouse_x Coordonnée en X de la position de la souris
 * \param mouse_y Coordonnée en Y de la position de la souris
 * \param milliseconds Le nombre de milliseconde à attendre avant d'arrêter la 
 *        fonction
 * \return un entier codant le type de l'évènement qui a été récupéré ( MLV_KEY 
 *         ou MLV_MOUSE_BUTTON ), ou MLV_NONE si le temps s'est écoulé.
 */
MLV_Event MLV_wait_keyboard_or_mouse_or_milliseconds(
	MLV_Keyboard_button* sym, MLV_Keyboard_modifier* mod, int* unicode,
	int* mouse_x, int* mouse_y,
	int milliseconds
);

/** \~french
 * \brief Convertit le code d'un évènement en une chaîne de caractères.
 *
 * \param event_code le code de l'évènement
 * \return La chaîne de caractères associée au code de l'évènement.
 */
const char* MLV_convert_event_to_string( MLV_Event event_code );

/** \~french
 * \brief Convertit le nom d'un évènement en son code associé.
 *
 * \param event_string le nom de l'évènement.
 * \return Le code de l'évènement associé à la chaîne de caractères.
 */
MLV_Event MLV_convert_string_to_event( const char* event_string );

/** \~french
 * \brief Convertit le code d'un état en une chaîne de caractères.
 *
 * \param state_code le code de l'état
 * \return La chaîne de caractères associée au code de l'état.
 */
const char* MLV_convert_button_state_to_string( MLV_Button_state state_code );

/** \~french
 * \brief Convertit le nom d'un état en son code associé.
 *
 * \param state_string le nom de l'état.
 * \return Le code de l'état associé à la chaîne de caractères.
 */
MLV_Button_state MLV_convert_string_to_button_state( const char* state_string );

/** \~french 
 *
 * \brief Cette fonction suspend l'exécution du programme, affiche une boîte 
 *        de saisie et attends que l'utilisateur rentre une phrase dans le 
 *        champs de la boîte ou qu'une temps (en millisecondes) donné en 
 *        paramètre s'écoule.
 *
 * La boîte de saisie contient deux zones de textes. 
 * La première zone ne peut pas être éditée par l'utilisateur et sert à 
 * afficher un message d'information. 
 * La deuxième est vide et peut être éditée par l'utilisateur.
 * Lorsque l'utilisateur appuie sur la touche entrée, le texte qui 
 * se trouve dans la zone de texte est renvoyé par la fonction
 * grâce au paramètre text.
 * Le texte, la taille et les couleurs de la boîte de saisie sont
 * paramétrables.
 * Si le temps sécoule complètement, alors text est mis à NULL.
 * 
 * MLV_wait_input_box() alloue lui même la mémoire associée au paramètre "text".
 * Par contre, après utilisation, vous devez libérer l'espace mémoire qui a été 
 * alloué.
 *
 * \param milliseconds Le temps à attendre en millisecondes.
 * \param top_left_corner_X     La coordonnée en X du coin Nord-Ouest de la 
 *                              boîte de saisie.
 * \param top_left_corner_Y     La coordonnée en Y du coin Nord-Ouest de la 
 *                              boîte de saisie.
 * \param width La largeur de la boîte de saisie.
 * \param height La hauteur de la boîte de saisie.
 * \param borderColor           La couleur de la bordure de la boîte de saisie.
 * \param textColor             La couleur du texte de la boîte de saisie.
 * \param backgroundColor       La couleur de fond de la boîte de saisie.
 * \param informativeMessage    Le message à afficher devant la boîte de saisie.
 * \param text                  L'addresse où sera placé la réponse donnée par 
 * \return un entier codant le type de l'évènement qui a été récupéré ( 
 *         MLV_INPUT_BOX ) ou MLV_NONE si le temps s'est écoulé.
 */
MLV_Event MLV_wait_input_box_or_milliseconds(
	int milliseconds,
	int top_left_corner_X, int top_left_corner_Y,
	int width, int height,
	MLV_Color borderColor, MLV_Color textColor,
	MLV_Color backgroundColor,
	const char* informativeMessage,
	char** text, ...
);

/** \~french 
 *
 * \brief Même chose que MLV_wait_input_box_or_milliseconds(), mais il est 
 *        possible de changer la fonte du du texte.
 * 
 * MLV_wait_input_box_with_font_or_milliseconds() alloue lui même la mémoire 
 * associée au paramètre "text".
 * Par contre, après utilisation, vous devez libérer l'espace mémoire qui a 
 * été alloué. Si le temps est écoulé, alot text est mis à NULL.
 *
 * \param top_left_corner_X   La coordonnée en X du coin Nord-Ouest de la 
 *                            boîte de saisie.
 * \param top_left_corner_Y   La coordonnée en Y du coin Nord-Ouest de la 
 *                            boîte de saisie.
 * \param width La largeur de la boîte de saisie.
 * \param height La hauteur de la boîte de saisie.
 * \param borderColor         La couleur de la bordure de la boîte de saisie.
 * \param textColor           La couleur du texte de la boîte de saisie.
 * \param backgroundColor     La couleur de fond de la boîte de saisie.
 * \param informativeMessage  Le message à afficher devant la boîte de saisie.
 * \param text                L'addresse où sera placé la réponse donnée par 
 *                            l'utilisateur.
 * \param font                La font du texte à utiliser.
 * \param milliseconds Le temps à attendre en millisecondes.
 * \return un entier codant le type de l'évènement qui a été récupéré ( 
 *         MLV_INPUT_BOX ) ou MLV_NONE si le temps s'est écoulé.
 */
MLV_Event MLV_wait_input_box_with_font_or_milliseconds(
	int milliseconds,
	int top_left_corner_X, int top_left_corner_Y,
	int width, int height,
	MLV_Color borderColor, MLV_Color textColor,
	MLV_Color backgroundColor,
	const char* informativeMessage,
	char** text,
	const MLV_Font* font, ...
);

/** \~french 
 * \brief Cette fonction suspend l'exécution du programme jusqu'à ce que 
 *        l'utilisateur écrive une phrase dans le champs de la boîte de 
 *        saisie passée en paramètre de la fonction ou qu'un nombre 
 *        de millisecondes fixées soient écoulée.
 *
 * \param input_box La boîte de saisie qui doit être observée.
 * \param text Le texte récupéré par la boîte de saisie.
 * \param milliseconds Le nombre de millisecondes à attendre.
 * \return un entier codant le type de l'évènement qui a été récupéré ( 
 *         MLV_INPUT_BOX ) ou MLV_NONE si le temps s'est écoulé.
 * \
 */
MLV_Event MLV_wait_particular_input_box_or_milliseconds(
	int milliseconds, MLV_Input_box* input_box, char** text
);

/** \~french 
 * \brief Cette fonction suspend l'exécution du programme jusqu'à ce que 
 *        l'utilisateur écrive une phrase dans le champs de la boîte de 
 *        saisie passée en paramètre de la fonction ou qu'un nombre 
 *        de secondes fixées soient écoulée.
 *
 * \param input_box La boîte de saisie qui doit être observée.
 * \param text Le texte récupéré par la boîte de saisie.
 * \param seconds Le nombre de secondes à attendre.
 * \return un entier codant le type de l'évènement qui a été récupéré ( 
 *         MLV_INPUT_BOX ) ou MLV_NONE si le temps s'est écoulé.
 * \
 */
MLV_Event MLV_wait_particular_input_box_or_seconds(
	MLV_Input_box* input_box, char** text, int seconds
);

#ifdef __cplusplus
}
#endif

#endif

