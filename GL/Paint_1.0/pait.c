#include</usr/include/cairo/cairo.h>
//#include<stdio.h>//#include<cairo.h>

int main()
{
	cairo_surface_t *surface;
	cairo_t *cr;
	//cairo_set_sourace_rgb();
	//cairo_rectangle();
	surface =cairo_image_surface_create(CAIRO_FORMAT_ARGB32,320,0);
	cr = cairo_create(surface);
	cairo_set_source_rgb(cr,0,1,0);
	cairo_rectangle(cr,10,10,200,200);
	cairo_fill(cr);
	cairo_move_to(cr,250,200);
	cairo_select_font_face(cr,"DongWen--Song",CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr,60);
	cairo_show_text(cr,"Hello world");
	cairo_surface_write_to_png(surface,"image.png");
	cairo_destroy(cr);
	cairo_surface_destroy(surface);
	return 0;
}
