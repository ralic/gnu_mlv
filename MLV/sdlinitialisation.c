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

#include <stdio.h>

#include "platform.h"

#ifndef MEMORY_DEBUG
#if defined( OS_WINDOWS )
#	include <SDL/SDL.h>
#elif defined( OS_APPLE )
#	include <SDL/SDL.h>
#else
#	include <SDL/SDL.h>
#endif
#else
#include "memory_debug.h"
#endif

#include "warning_error.h"

#include "memory_management.h"

int mlv_sdl_is_initialised = 0;

void initialise_sdl(){
	if( ! mlv_sdl_is_initialised ){
		if(
			SDL_Init(
				SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO 
	#if defined( OS_LINUX ) // SDL thread is not supported on Windows and MacOSX
				| SDL_INIT_EVENTTHREAD  // Cette option est importante !
									  // Elle permet de faire en sorte 
					  // que le filtrage des évenements soit fait dés 
					  // réception d'un evenement de la part de l'OS
					  // Si cette option n'est pas activée, le filtre 
					  // d'evenement est applique seulement après un 
					  // appel à poll_event. Dans ce cas la gestion
					  // de l'arret automatique du programme après 
					  // utilisation de la croix des fenetre ne 
					  // fonctione plus correctement. En effet, si 
					  // l'utilisateur n'utilise pas de fonction mettant
					  // en jeu des évènement, le filtre n'est jamais
					  // appelé et le mécanisme d'arret automatique 
					  // non plus.
	#endif
			) <0 
		){
			fprintf( stderr, "Unable to init SDL: %s\n", SDL_GetError() );
			exit(1);
		}
	}
}

void free_sdl(){
	if( mlv_sdl_is_initialised ){
		mlv_sdl_is_initialised = 0;
		SDL_Quit();
	}
}
