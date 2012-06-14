#ifndef PHYSICS_H
#define PHYSICS_H

#include "types.h"

void physics_init();
void physics_close();

int physics_create_world(double gravity);
void physics_destroy_world(int world);

int physics_create_fixed_plane(int world, double pos_x, double pos_y, double pos_z, double width, double height);
int physics_create_box(int world, double pos_x, double pos_y, double pos_z, double width, double height, double length, double mass);
//int physics_create_plane();
//int physics_create_rigdbody();
void physics_destroy_object(int object);

void physics_update(double time);

Vertex physics_get_position(int object);
int physics_get_triangles(int object, Vertex *vertices, int triangles);

#endif

