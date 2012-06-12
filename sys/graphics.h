#ifndef GRAPHICS_H
#define GRAPHICS_H

void graphics_init(int argc, char **argv);
void graphics_close();

int graphics_create_window(const char *title, int left, int top, int width, int height);
void graphics_destroy_window(int window);

void graphics_set_updater(double update_interval, void(*updater)(double));
void graphics_set_typer(void(*typer)(int key));

void graphics_main_loop();

void graphics_color(unsigned char red, unsigned char green, unsigned char blue);

//void graphics_draw_sphere(...);
//void graphics_draw_box(...);
//void graphics_draw_plane(...);

#endif

