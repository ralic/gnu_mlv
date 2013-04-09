/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2013 Adrien Boussicault, Marc Zipstein
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
 * \file MLV_text_va.h
 *
 * \author Adrien Boussicault
 * \author Marc Zipstein
 *
 * \brief Ce fichier définit différents prototypes des fonctions permmettant
 *        d'afficher du texte et des boîtes de dialogues.
 */

#ifndef __MLV__MLV_TEXT_VA_H__
#define __MLV__MLV_TEXT_VA_H__

#include "MLV_color.h"
#include "MLV_image.h"
#include "MLV_text.h"

#ifdef __cplusplus
extern "C" {
#endif

void MLV_draw_text_va(
	int x, int y, const char *text, MLV_Color color, va_list pile
);

void MLV_draw_text_with_font_va(
	int x, int y, const char *text, const MLV_Font* font, MLV_Color color, 
	va_list pile
);

void MLV_draw_text_with_font_on_image_va(
	int x, int y, const char *text, const MLV_Font* font, MLV_Color color, 
	MLV_Image* image, va_list pile
);

void MLV_get_size_of_text_va(
	const char *text, int *width, int *height, va_list pile
);

void MLV_get_size_of_text_with_font_va(
	const char *text, int *width, int *height, const MLV_Font* font, 
	va_list pile
);

void MLV_draw_adapted_text_box_with_font_va(
	int x, int y,
	const char* message,
	const MLV_Font* font, 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	va_list pile
);

void MLV_draw_adapted_text_box_va(
	int x, int y,
	const char* message,
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification, va_list pile
);

void MLV_draw_adapted_text_box_on_image_va(
	int x, int y,
	const char* message,
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	MLV_Image* image, va_list pile
);

void MLV_draw_adapted_text_box_with_font_on_image_va(
	int x, int y,
	const char* message,
	const MLV_Font* font, 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	MLV_Image* image, va_list pile
);

int MLV_get_size_of_adapted_text_box_va(
	const char* message,
	int sizeInterligne,
	int *result_width, int *result_height,
	va_list pile
);

int MLV_get_size_of_adapted_text_box_with_font_va(
	const char* message,
	const MLV_Font* font, 
	int sizeInterligne,
	int *result_width, int *result_height,
	va_list pile
);


void MLV_draw_text_box_with_font_va( 
	int x, int y, 
	int width, int height, 
	const char* message , 
	const MLV_Font* font, 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	MLV_Horizontal_position horizontal_position,
	MLV_Vertical_position vertical_position,
	va_list pile
);

void MLV_draw_text_box_va( 
	int x, int y, 
	int width, int height, 
	const char* message , 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	MLV_Horizontal_position horizontal_position,
	MLV_Vertical_position vertical_position,
	va_list pile
);

void MLV_draw_text_box_with_font_on_image_va( 
	int x, int y, 
	int width, int height, 
	const char* message , 
	MLV_Font* font, 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	MLV_Horizontal_position horizontal_position,
	MLV_Vertical_position vertical_position,
	MLV_Image* image,
	va_list pile
);

void MLV_draw_text_box_on_image_va( 
	int x, int y, 
	int width, int height, 
	const char* message , 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	MLV_Horizontal_position horizontal_position,
	MLV_Vertical_position vertical_position,
	MLV_Image* image,
	va_list pile
);

#ifdef __cplusplus
}
#endif

#endif

