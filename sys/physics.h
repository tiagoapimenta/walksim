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
Vertex physics_get_lengths(int object);
Transform physics_get_rotation(int object);

int physics_get_triangles(int object, Vertex *vertices, int triangles);

int physics_create_hinge_joint(int world, int object1, int object2, double x, double y, double z, double axisX, double axisY, double axisZ);
void physics_destroy_joint(int joint);

Vertex physics_get_hinge_anchor(int joint);
double physics_get_hinge_angle(int joint);
double physics_get_hinge_angle_rate(int joint);
void physics_add_hinge_torque(int joint, double torque);

void physics_set_collider(void(*collider)(int objectA, int objectB));

#endif

