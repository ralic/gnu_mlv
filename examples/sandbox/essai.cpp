#include "window.hpp"

void f( mlv::image_t & img ){
	int x =0, y=0, radius = 0;
	int x1=0, x2=0, ax= 0, ay=0, bx = 0, by=0, width = 0, height = 0;
	int radius_x = 0, radius_y=0;
	int cx=0, cy=0;
	int y1 = 0, y2 = 0;
	mlv::color_t color = MLV_COLOR_GREEN;
	img.draw_circle(x, y, radius, color);
	img.draw_filled_circle(x, y, radius, color);
	img.draw_ellipse(x, y, radius_x, radius_y, color);
	img.draw_filled_ellipse(x, y, radius_x, radius_y, color);
	img.draw_triangle(ax, ay, bx, by, cx, cy, color);
	img.draw_filled_triangle(ax, ay, bx, by, cx, cy, color);
	img.draw_rectangle(x, y, width, height, color);
	img.draw_filled_rectangle(x, y, width, height, color);
	img.draw_line(x1, y1, x2, y2, color);
	img.draw_pixel(x, y, color);
	img.draw_point(x, y, color);

	int nb_points = 4;
	mlv::point_t p[4] = { {1,3}, {2,4}, {4,2}, {4,4} };
	img.draw_filled_polygon( p, nb_points, color );
	img.draw_polygon( p, nb_points, color );
	img.draw_bezier_curve( p, nb_points, color);
}

void draw( mlv::window_t& window ){

	int x =0, y=0, radius = 0;
	int x1=0, x2=0, ax= 0, ay=0, bx = 0, by=0, width = 0, height = 0;
	int radius_x = 0, radius_y=0;
	int cx=0, cy=0;
	int y1 = 0, y2 = 0;
	mlv::color_t color = MLV_COLOR_GREEN;
	window.draw_circle(x, y, radius, color);
	window.draw_filled_circle(x, y, radius, color);
	window.draw_ellipse(x, y, radius_x, radius_y, color);
	window.draw_filled_ellipse(x, y, radius_x, radius_y, color);
	window.draw_triangle(ax, ay, bx, by, cx, cy, color);
	window.draw_filled_triangle(ax, ay, bx, by, cx, cy, color);
	window.draw_rectangle(x, y, width, height, color);
	window.draw_filled_rectangle(x, y, width, height, color);
	window.draw_line(x1, y1, x2, y2, color);
	window.draw_pixel(x, y, color);
	window.draw_point(x, y, color);

	int nb_points = 4;
	mlv::point_t p[4] = { {1,3}, {2,4}, {4,2}, {4,4} };
	window.draw_filled_polygon( p, nb_points, color );
	window.draw_polygon( p, nb_points, color );
	window.draw_bezier_curve( p, nb_points, color);

}

#if __cplusplus >= 201100
void g( mlv::image_t && img ){
	img.draw_line(3,3,5,5,MLV_COLOR_GREEN);
}
#endif

int main(){
	mlv::window_t window( "essai", "essai", 640, 480 );

	mlv::image_t image1( "essai.jpg" );

	mlv::image_t image2( 640, 489 );

	mlv::image_t image3( image1 );

	mlv::image_t image4( std::move( image1 ) );
	

	f( image1 );

#if __cplusplus >= 201100
	g( mlv::image_t("essai.jpg") );
#endif

	draw(window);
	return 0;
}
