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

#include <string>
#include <cassert>
#include <MLV/MLV_window.h>
#include <MLV/MLV_shape.h>
#include <MLV/MLV_text.h>
#include <MLV/MLV_time.h>
#include <MLV/MLV_random.h>
#include <MLV/MLV_mouse.h>
#include <MLV/MLV_keyboard.h>

namespace mlv {

typedef struct {
	MLV_Keyboard_button sym;
	MLV_Keyboard_modifier mod;
	int unicode;
} key_t;

/** \~french 
 * \brief Renvoie 0 ou 1 aléatoirement.
 *
 * \return 0 ou 1 aléatoirement.
 */
int random_boolean(){
	return MLV_get_random_boolean();
}

/** \~french 
 * \brief Renvoie un entier aléatoire choisi dans un intervalle donné en 
 *        paramètre.
 *
 * \param begin Borne inférieur de l'intervalle ( inclusif )
 * \param end Borne supérieur de l'intervalle ( inclusif )
 * \return  Un entier aléatoire choisi dans l'intervalle [begin, end].
 */
int random_integer(int begin, int end){
	return MLV_get_random_integer(begin, end);
}

/** \~french 
 * \brief Renvoie un réel aléatoire choisi dans un intervalle donné en 
 *        paramètre.
 *
 * \param begin Borne inférieur de l'intervalle ( inclusif )
 * \param end Borne supérieur de l'intervalle ( inclusif )
 * \return Un réel aléatoire choisi dans l'intervalle [begin, end].
 */
double random_double(double begin, double end){
	return MLV_get_random_double(begin, end);
}


typedef MLV_Color color_t;

namespace system {

int desktop_height( ){
	return MLV_get_desktop_height();
}
int desktop_width(){
	return MLV_get_desktop_width();
}

} // namesapce system

struct point_t {
	point_t(): x(0), y(0) {}
	point_t(int x, int y): x(x), y(y) {}

	int x;
	int y;
};

void _copy_array( int ** vx, int **vy, const point_t* array, int nb_points ){
	*vx = new int[ nb_points ];
	*vy = new int[ nb_points ];
	for( int i = 0; i < nb_points; i++ ){
		(*vx)[i] = array[i].x;
		(*vy)[i] = array[i].y;
	}
}

void _free_array( int * vx, int *vy ){
	delete vx;
	delete vy;
}

class image_t {
	private:
		friend class window_t;
		MLV_Image * image;
		void _free(){
			if( image ){
				MLV_free_image( image );
			}
		}
	public:
		image_t(): image(0) {}
		image_t( const std::string & file_path ):
			image( MLV_load_image( file_path.c_str() ) )
		{ }
		image_t( unsigned int width, unsigned int height ):
			image( MLV_create_image( width, height ) )
		{ }
		image_t( const image_t & image ):
			image( ( image.image )? MLV_copy_image( image.image ): 0 )
		{ }
		image_t & operator=( const image_t& image ){
			if( this != &image ){
				_free();
				this->image = MLV_copy_image( image.image );
			}
			return *this;
		}
		#if __cplusplus >= 201100
		image_t( image_t && image ): image( image.image ) {
			image.image = 0;
		}
		image_t & operator=( image_t && image ){
			if( this != &image ){
				_free();
				this->image = image.image;
				image.image = 0;
			}
			return *this;
		}
		#endif
		~image_t(){
			_free();
		}

		/** \~french 
		 * \brief Retourne la largeur d'une image donnée.
		 *
		 * \return La largeur de l'image.
		 */
		int width() const {
			assert( image );
			return MLV_get_image_width( image );
		}

		/** \~french 
		 * \brief Retourne la hauteur d'une image donnée.
		 *
		 * \return La hauteur de l'image
		 */
		int height() const {
			assert( image );
			return MLV_get_image_height( image );
		}

		/** \~french 
		 * \brief Redimensionne l'image en ne respectant pas les proportions de l'image
		 *        originale.
		 *
		 * La hauteur et la largeur de la nouvelle image deviennent respectivement la 
		 * hauteur et la largeur passées en paramètres.
		 *
		 * \param width La largeur de l'image.
		 * \param height La hauteur de l'image.
		 */
		void resize( int width, int height ){
			assert( image );
			MLV_resize_image( image, width, height );
		}

		/** \~french 
		 * \brief Modifie l'image en réalisant une réflexion horizontale.
		 */ 
		void horizontal_mirror(){
			MLV_horizontal_image_mirror( image );
		}

		/** \~french 
		 * \brief Modifie l'image en réalisant une réflexion verticale.
		 */ 
		void vertical_mirror(){
			MLV_vertical_image_mirror( image );
		}

		/** \~french 
		 * \brief Cette fonction redimensionne l'image en repsectant les proportions 
		 *        de l'image originale.
		 *
		 * L'image résultat est la plus grande image possible incluse dans le rectangle
		 * de largeur width et de hauteur height.
		 *
		 * L'utilisateur peut entrer un entier négatif pour les champs width et height.
		 * Ces champs ne sont alors pas pris en compte dans le redimensionnement de 
		 * l'image. Dans ce cas, si le paramètre width (resp. height) est 
		 * négatif, alors l'image finale aura pour largeur (resp. hauteur) la taille 
		 * spécifiée dans le paramètre width (resp. height).
		 *
		 * \param width La nouvelle largeur de l'image.
		 * \param height La nouvlle hauteur de l'image.
		 */ 
		void proportional_resize( int width, int height ){
			MLV_resize_image_with_proportions( image, width, height );
		}

		/** \~french 
		 * \brief Modifie l'image à l'aide d'une homotétie ( Étire l'image )
		 *
		 * \param scalar Coefficient de proportionalité de l'homotétie ( >1 l'image est
		 *               agrandie, <1 l'image est rétrécie ). 
		 */
		void scale( double scalar ){
			MLV_scale_image( image, scalar );
		}

		/** \~french 
		 * \brief Éffectue une rotation sur une image donnée.
		 *
		 * \param rotation L'angle de la rotation.
		 */
		void rotate( MLV_Image* image, double rotation ){
			MLV_rotate_image( image, rotation );
		}

		/** \~french 
		 * \brief Étire l'image suivant l'axe X et l'axe Y avec des coefficients de 
		 *        proportionnalité différents pour les deux axes.
		 *
		 * \param scalar_x Le coéfficient de proportionnalité de l'axe X.
		 * \param scalar_y Le coéfficient de proportionnalité de l'axe Y.
		 */
		void scale_xy( double scalar_x, double scalar_y ){
			MLV_scale_xy_image( image, scalar_x, scalar_y );
		}


		/** \~french 
		 * \brief Dessine un cercle à une position et un rayon spécifiés en paramètres.
		 **
		 * \param x La coordonnée en X du centre.
		 * \param y La coordonnée en Y du centre.
		 * \param radius Le rayon du cercle.
		 * \param color La couleur du tracé.
		 */
		void draw_circle(int x, int y, int radius, color_t color){
			MLV_draw_circle_on_image(x, y, radius, color, image);
		}

		/** \~french 
		 * \brief Dessine un disque plein dont le centre et le rayon sont passés en 
		 *        paramètres.
		 *
		 * \param x La coordonnée en X du centre.
		 * \param y La coordonnée en Y du centre.
		 * \param radius Le rayon du cercle.
		 * \param color La couleur du tracé.
		 */
		void draw_filled_circle(int x, int y, int radius, color_t color){
			MLV_draw_filled_circle_on_image(x, y, radius, color, image);
		}

		/** \~french 
		 * \brief Dessine une ellipse.
		 *
		 * \param x La coordonnée en X du centre de l'ellipse.
		 * \param y La coordonnée en Y du centre de l'ellipse.
		 * \param radius_x Le rayon en X de l'ellipse.
		 * \param radius_y Le rayon en Y de l'ellipse.
		 * \param color La couleur du tracé.
		 */
		void draw_ellipse(int x, int y, int radius_x, int radius_y, color_t color){
			MLV_draw_ellipse_on_image(x, y, radius_x, radius_y, color, image);
		}

		/** \~french 
		 * \brief Dessine une ellipse pleine.
		 *
		 * \param x La coordonnée en X du centre de l'ellipse.
		 * \param y La coordonnée en Y du centre de l'ellipse.
		 * \param radius_x Le rayon en X de l'ellipse.
		 * \param radius_y Le rayon en Y de l'ellipse.
		 * \param color La couleur du tracé.
		 */
		void draw_filled_ellipse(int x, int y, int radius_x, int radius_y, color_t color){
			MLV_draw_filled_ellipse_on_image(x, y, radius_x, radius_y, color, image);
		}

		/** \~french 
		 * \brief Dessine un polygone à partir d'une liste de sommets.
		 *
		 * \param vx La liste des coordonnées en X des différents sommets du polygone.
		 * \param vy La liste des coordonnées en Y des différents sommets du polygone.
		 * \param nb_points Le nombre de sommets du polygone.
		 * \param color La couleur du tracé.
		 */
		void draw_polygon(const point_t * array, int nb_points, color_t color){
			int *vx, *vy;
			_copy_array( &vx, &vy, array, nb_points );
			MLV_draw_polygon_on_image(vx, vy, nb_points, color, image);
			_free_array( vx, vy );
		}

		/** \~french 
		 * \brief Dessine un triangle (vide).
		 *
		 * \param ax La coordonnée en X du premier point du triangle.
		 * \param ay La coordonnée en Y dy premier point du traingle.
		 * \param bx La coordonnée en X du deuxième point du triangle.
		 * \param by La coordonnée en Y dy deuxième point du traingle.
		 * \param cx La coordonnée en X du troisième point du triangle.
		 * \param cy La coordonnée en Y dy troisième point du traingle.
		 * \param color La couleur du triangle.
		 */
		void draw_triangle(int ax, int ay, int bx, int by, int cx, int cy, color_t color){
			MLV_draw_triangle_on_image(ax, ay, bx, by, cx, cy, color, image);
		}

		/** \~french 
		 * \brief Dessine un polygone plein à partir d'une liste de sommets.
		 *
		 * \param vx La liste des coordonnées en X des différents sommets du polygone.
		 * \param vy La liste des coordonnées en Y des différents sommets du polygone.
		 * \param nb_points Le nombre de sommets du polygone.
		 * \param color La couleur du tracé.
		 */
		void draw_filled_polygon(const point_t * array, int nb_points, color_t color){
			int *vx, *vy;
			_copy_array( &vx, &vy, array, nb_points );
			MLV_draw_filled_polygon_on_image(vx, vy, nb_points, color, image);
			_free_array( vx, vy );
		}

		/** \~french 
		 * \brief Dessine un triangle plein.
		 *
		 * \param ax La coordonnée en X du premier point du triangle.
		 * \param ay La coordonnée en Y dy premier point du traingle.
		 * \param bx La coordonnée en X du deuxième point du triangle.
		 * \param by La coordonnée en Y dy deuxième point du traingle.
		 * \param cx La coordonnée en X du troisième point du triangle.
		 * \param cy La coordonnée en Y dy troisième point du traingle.
		 * \param color La couleur du triangle.
		 */
		void draw_filled_triangle(int ax, int ay, int bx, int by, int cx, int cy, color_t color){
			MLV_draw_filled_triangle_on_image(ax, ay, bx, by, cx, cy, color, image);
		}


		/** \~french 
		 * \brief Dessine une courbe de Bézier à partir d'une liste de sommets.
		 *
		 * \param vx La liste des coordonnées en X des différents sommets de la courbe.
		 * \param vy La liste des coordonnées en Y des différents sommets de la courbe.
		 * \param nb_points Le nombre de sommets disponibles pour dessiner la courbe de 
		 *                Bézier.
		 * \param color La couleur du tracé.
		 */
		void draw_bezier_curve(const point_t * array,  int nb_points, color_t color){
			int *vx, *vy;
			_copy_array( &vx, &vy, array, nb_points );
			MLV_draw_bezier_curve_on_image(vx, vy, nb_points, color, image);
			_free_array( vx, vy );
		}

		/** \~french 
		 * \brief Dessine un rectangle dont la taille, la couleur et la position du 
		 *        sommet Nord-Ouest sont données en paramètres.
		 *
		 * \param x La coordonnée en X du sommet Nord-Ouest du rectangle.
		 * \param y La coordonnée en Y du sommet Nord-Ouest du rectangle.
		 * \param width La largeur du rectangle.
		 * \param height La hauteur du rectangle.
		 * \param color La couleur du tracé.
		 */
		void draw_rectangle(int x, int y, int width, int height, color_t color){
			MLV_draw_rectangle_on_image(x, y, width, height, color, image);
		}

		/** \~french 
		 * \brief Dessine un rectangle plein dont la taille, la couleur et la position 
		 *        du sommet Nord-Ouest sont données en paramètres.
		 *
		 * \param x La coordonnée en X du sommet Nord-Ouest du rectangle.
		 * \param y La coordonnée en Y du sommet Nord-Ouest du rectangle.
		 * \param width La largeur du rectangle.
		 * \param height La hauteur du rectangle.
		 * \param color La couleur du tracé.
		 */
		void draw_filled_rectangle(int x, int y, int width, int height, color_t color){
			MLV_draw_filled_rectangle_on_image(x, y, width, height, color, image);
		}

		/** \~french 
		 * \brief Dessine une ligne.
		 *
		 * \param x1 La coordonnée en X de la première extrémité de la ligne.
		 * \param y1 La coordonnée en Y de la première extrémité de la ligne.
		 * \param x2 La coordonnée en X de la deuxième extrémité de la ligne.
		 * \param y2 La coordonnée en Y de la deuxième extrémité de la ligne.
		 * \param color La couleur du tracé.
		 */
		void draw_line(int x1, int y1, int x2, int y2, color_t color){
			MLV_draw_line_on_image(x1, y1, x2, y2, color, image);
		}

		/** \~french 
		 * \brief Dessine un pixel dont les coordonnées sont passées en paramètres.
		 *
		 * \param x La coordonnée en X du pixel.
		 * \param y La coordonnée en Y du pixel.
		 * \param color La couleur du tracé.
		 */
		void draw_pixel(int x, int y, color_t color){
			MLV_draw_pixel_on_image(x, y, color, image);
		}

		/** \~french 
		 * \brief Dessine un point dont les coordonnées sont passées en paramètres.
		 *        Cette fonction est identique à MLV_draw_pixel.
		 *
		 * \param x La coordonnée en X du point.
		 * \param y La coordonnée en Y du point.
		 * \param color La couleur du tracé.
		 */
		void draw_point(int x, int y, color_t color){
			MLV_draw_point_on_image(x, y, color, image);
		}
};

class window_t {
	public:
		window_t(
			const std::string & window_name, const std::string & icon_name, 
			unsigned int width, unsigned int height
		){
			MLV_create_window(
				window_name.c_str(), icon_name.c_str(), width, height  
			);
		}
		window_t(
			const std::string & window_name, const std::string & icon_name, 
			unsigned int width, unsigned int height,
			const std::string & path_to_font, unsigned int size_font
		){
			MLV_create_window_with_default_font(
				window_name.c_str(), icon_name.c_str(), width, height,
				path_to_font.c_str(), size_font
			);
		}
		~window_t() {
			MLV_free_window();
		}
		void set_font(
			const std::string & path_to_font, unsigned int size_font 
		){
			MLV_change_default_font( path_to_font.c_str(), size_font );
		}
		void set_full_screen( bool full_screen ){
			if( full_screen ){
				MLV_enable_full_screen();
			}else{
				MLV_disable_full_screen();
			}
		}
		void resize( unsigned int width, unsigned int height ){
			MLV_change_window_size( width, height );
		}
		void set_caption(
			const std::string & window_name, const std::string & icon_name
		){
			MLV_change_window_caption(window_name.c_str(), icon_name.c_str());
		}
		bool full_screen( ) const {
			return MLV_is_full_screen() != 0;
		}
		void update(){
			MLV_update_window();
		}
		int width() const {
			return MLV_get_window_height( );
		}
		int height() const {
			return MLV_get_window_width( );
		}
		void clear( color_t color ){
			MLV_clear_window( color );
		}

		void draw( const image_t& image, int x, int y ){
			MLV_draw_image( image.image, x, y );
		}
		void partial_draw( 
			const image_t& image, int x, int y,
			int top_left, int top_right, int width, int height 
		){
			MLV_draw_partial_image(
				image.image, top_left, top_right, width, height, x, y 
			);
		}


		/** \~french 
		 * \brief Dessine un cercle à une position et un rayon spécifiés en paramètres.
		 **
		 * \param x La coordonnée en X du centre.
		 * \param y La coordonnée en Y du centre.
		 * \param radius Le rayon du cercle.
		 * \param color La couleur du tracé.
		 */
		void draw_circle(int x, int y, int radius, MLV_Color color){
			MLV_draw_circle( x, y, radius, color);
		}

		/** \~french 
		 * \brief Dessine un disque plein dont le centre et le rayon sont passés en 
		 *        paramètres.
		 *
		 * \param x La coordonnée en X du centre.
		 * \param y La coordonnée en Y du centre.
		 * \param radius Le rayon du cercle.
		 * \param color La couleur du tracé.
		 */
		void draw_filled_circle(int x, int y, int radius, MLV_Color color){
			MLV_draw_filled_circle( x, y, radius, color);
		}

		/** \~french 
		 * \brief Dessine une ellipse.
		 *
		 * \param x La coordonnée en X du centre de l'ellipse.
		 * \param y La coordonnée en Y du centre de l'ellipse.
		 * \param radius_x Le rayon en X de l'ellipse.
		 * \param radius_y Le rayon en Y de l'ellipse.
		 * \param color La couleur du tracé.
		 */
		void draw_ellipse(int x, int y, int radius_x, int radius_y, MLV_Color color){
			MLV_draw_ellipse( x, y, radius_x, radius_y, color);
		}

		/** \~french 
		 * \brief Dessine une ellipse pleine.
		 *
		 * \param x La coordonnée en X du centre de l'ellipse.
		 * \param y La coordonnée en Y du centre de l'ellipse.
		 * \param radius_x Le rayon en X de l'ellipse.
		 * \param radius_y Le rayon en Y de l'ellipse.
		 * \param color La couleur du tracé.
		 */
		void draw_filled_ellipse(int x, int y, int radius_x, int radius_y, MLV_Color color){
			MLV_draw_filled_ellipse( x, y, radius_x, radius_y, color);
		}

		/** \~french 
		 * \brief Dessine un polygone à partir d'une liste de sommets.
		 *
		 * \param vx La liste des coordonnées en X des différents sommets du polygone.
		 * \param vy La liste des coordonnées en Y des différents sommets du polygone.
		 * \param nb_points Le nombre de sommets du polygone.
		 * \param color La couleur du tracé.
		 */
		void draw_polygon(const point_t* array, int nb_points, MLV_Color color){
			int *vx, *vy;
			_copy_array( &vx, &vy, array, nb_points );
			MLV_draw_polygon( vx,  vy, nb_points, color);
			_free_array( vx, vy );
		}

		/** \~french 
		 * \brief Dessine un triangle (vide).
		 *
		 * \param ax La coordonnée en X du premier point du triangle.
		 * \param ay La coordonnée en Y dy premier point du traingle.
		 * \param bx La coordonnée en X du deuxième point du triangle.
		 * \param by La coordonnée en Y dy deuxième point du traingle.
		 * \param cx La coordonnée en X du troisième point du triangle.
		 * \param cy La coordonnée en Y dy troisième point du traingle.
		 * \param color La couleur du triangle.
		 */
		void draw_triangle(int ax, int ay, int bx, int by, int cx, int cy, MLV_Color color){
			MLV_draw_triangle( ax, ay, bx, by, cx, cy, color);
		}

		/** \~french 
		 * \brief Dessine un polygone plein à partir d'une liste de sommets.
		 *
		 * \param vx La liste des coordonnées en X des différents sommets du polygone.
		 * \param vy La liste des coordonnées en Y des différents sommets du polygone.
		 * \param nb_points Le nombre de sommets du polygone.
		 * \param color La couleur du tracé.
		 */
		void draw_filled_polygon(const point_t* array, int nb_points, MLV_Color color){
			int *vx, *vy;
			_copy_array( &vx, &vy, array, nb_points );
			MLV_draw_filled_polygon( vx,  vy, nb_points, color);
			_free_array( vx, vy );
		}

		/** \~french 
		 * \brief Dessine un triangle plein.
		 *
		 * \param ax La coordonnée en X du premier point du triangle.
		 * \param ay La coordonnée en Y dy premier point du traingle.
		 * \param bx La coordonnée en X du deuxième point du triangle.
		 * \param by La coordonnée en Y dy deuxième point du traingle.
		 * \param cx La coordonnée en X du troisième point du triangle.
		 * \param cy La coordonnée en Y dy troisième point du traingle.
		 * \param color La couleur du triangle.
		 */
		void draw_filled_triangle(int ax, int ay, int bx, int by, int cx, int cy, MLV_Color color){
			MLV_draw_filled_triangle( ax, ay, bx, by, cx, cy, color);
		}


		/** \~french 
		 * \brief Dessine une courbe de Bézier à partir d'une liste de sommets.
		 *
		 * \param vx La liste des coordonnées en X des différents sommets de la courbe.
		 * \param vy La liste des coordonnées en Y des différents sommets de la courbe.
		 * \param nb_points Le nombre de sommets disponibles pour dessiner la courbe de 
		 *                Bézier.
		 * \param color La couleur du tracé.
		 */
		void draw_bezier_curve(const point_t* array, int nb_points, MLV_Color color){
			int *vx, *vy;
			_copy_array( &vx, &vy, array, nb_points );
			MLV_draw_bezier_curve( vx,  vy, nb_points, color);
			_free_array( vx, vy );
		}

		/** \~french 
		 * \brief Dessine un rectangle dont la taille, la couleur et la position du 
		 *        sommet Nord-Ouest sont données en paramètres.
		 *
		 * \param x La coordonnée en X du sommet Nord-Ouest du rectangle.
		 * \param y La coordonnée en Y du sommet Nord-Ouest du rectangle.
		 * \param width La largeur du rectangle.
		 * \param height La hauteur du rectangle.
		 * \param color La couleur du tracé.
		 */
		void draw_rectangle(int x, int y, int width, int height, MLV_Color color){
			MLV_draw_rectangle( x, y, width, height, color);
		}

		/** \~french 
		 * \brief Dessine un rectangle plein dont la taille, la couleur et la position 
		 *        du sommet Nord-Ouest sont données en paramètres.
		 *
		 * \param x La coordonnée en X du sommet Nord-Ouest du rectangle.
		 * \param y La coordonnée en Y du sommet Nord-Ouest du rectangle.
		 * \param width La largeur du rectangle.
		 * \param height La hauteur du rectangle.
		 * \param color La couleur du tracé.
		 */
		void draw_filled_rectangle(int x, int y, int width, int height, MLV_Color color){
			MLV_draw_filled_rectangle( x, y, width, height, color);
		}

		/** \~french 
		 * \brief Dessine une ligne.
		 *
		 * \param x1 La coordonnée en X de la première extrémité de la ligne.
		 * \param y1 La coordonnée en Y de la première extrémité de la ligne.
		 * \param x2 La coordonnée en X de la deuxième extrémité de la ligne.
		 * \param y2 La coordonnée en Y de la deuxième extrémité de la ligne.
		 * \param color La couleur du tracé.
		 */
		void draw_line(int x1, int y1, int x2, int y2, MLV_Color color){
			MLV_draw_line( x1, y1, x2, y2, color);
		}

		/** \~french 
		 * \brief Dessine un pixel dont les coordonnées sont passées en paramètres.
		 *
		 * \param x La coordonnée en X du pixel.
		 * \param y La coordonnée en Y du pixel.
		 * \param color La couleur du tracé.
		 */
		void draw_pixel(int x, int y, MLV_Color color){
			MLV_draw_pixel( x, y, color);
		}

		/** \~french 
		 * \brief Dessine un point dont les coordonnées sont passées en paramètres.
		 *        Cette fonction est identique à MLV_draw_pixel.
		 *
		 * \param x La coordonnée en X du point.
		 * \param y La coordonnée en Y du point.
		 * \param color La couleur du tracé.
		 */
		void draw_point(int x, int y, MLV_Color color){
			MLV_draw_point( x, y, color);
		}


		/** \~french 
		 * \brief Imprime un texte donné à une position et une couleur données.
		 * 
		 * Le texte est imprimé à l'aide de la fonte de caractères par default de la 
		 * bibliothèque MLV.
		 *
		 * \param x Coordonnée en X du coin Nord-Ouest du texte
		 * \param y Coordonnée en Y du coin Nord-Ouest du texte
		 * \param text texte à afficher
		 * \param color couleur du tracé
		 */
		void draw_text( int x, int y, const std::string & text, MLV_Color color ){
			MLV_draw_text( x, y, text.c_str(), color );
		}

		/** \~french 
		 * \brief Le programme s'intérompt pendant un nombre de secondes.
		 *
		 * \param seconds Le nombre de secondes à attendre.
		 */
		void wait_seconds( int seconds ){
			MLV_wait_seconds(seconds);
		}

		/** \~french 
		 * \brief Le programme s'intérompt pendant un nombre de milli-secondes donné 
		 *        en paramètre.
		 *
		 * \param milliseconds Le nombre de milli-secondes à attendre.
		 */
		void wait_milliseconds( int milliseconds ){
			MLV_wait_milliseconds(milliseconds);
		}

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
		 */
		void wait_mouse(int & x, int & y){
			MLV_wait_mouse(&x, &y);
		}

		/** \~french 
		 * \brief Suspend l'exécution jusqu'à ce que l'utilisateur appuie sur une touche
		 *        du  clavier.
		 * 
		 * Lorsque l'utilisateur appuie sur une touche, la fonction remplit le contenu 
		 * des trois paramètres sym, mod et unicode correspondant respectivement au 
		 * code de la touche, au mode dans lequel se trouve le clavier 
		 * (majuscule etc ...) et au caractère unicode obtenu en combinant le mode du 
		 * clavier et le code de la touche appuyée.
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
		 */
		void wait_keyboard( key_t & key ){
			MLV_wait_keyboard( &key.sym, &key.mod, &key.unicode );
		}

	};

} // namespace mlv

