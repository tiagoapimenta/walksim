#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "types.h"

#define KEY_ESCAPE     27
#define KEY_SPACE      32

#define KEY_SHIFT     256
#define KEY_CONTROL   257
#define KEY_ALT       258
#define KEY_F1        259
#define KEY_F2        260
#define KEY_F3        261
#define KEY_F4        262
#define KEY_F5        263
#define KEY_F6        264
#define KEY_F7        265
#define KEY_F8        266
#define KEY_F9        267
#define KEY_F10       268
#define KEY_F11       269
#define KEY_F12       270
#define KEY_LEFT      271
#define KEY_UP        272
#define KEY_RIGHT     273
#define KEY_DOWN      274
#define KEY_PAGE_UP   275
#define KEY_PAGE_DOWN 276
#define KEY_HOME      277
#define KEY_END       278
#define KEY_INSERT    279

void graphics_init(int argc, char **argv);
void graphics_close();

int graphics_create_window(const char *title, int left, int top, int width, int height);
void graphics_destroy_window(int window);

void graphics_set_updater(double update_interval, void(*updater)(double));
void graphics_set_typer(void(*typer)(int key));
void graphics_set_typer_release(void(*typer)(int key));

void graphics_main_loop();

void graphics_color(unsigned char red, unsigned char green, unsigned char blue);

void graphics_draw_triangles(Vertex *vertices, int triangles);
//void graphics_draw_sphere(...);
//void graphics_draw_box(...);
//void graphics_draw_plane(...);

void graphics_translate(double x, double y, double z);
void graphics_rotate(double x, double y, double z);
void graphics_scale(double x, double y, double z);

#endif

