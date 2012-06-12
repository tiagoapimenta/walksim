#ifndef PHYSICS_H
#define PHYSICS_H

void physics_init();
void physics_close();

int physics_create_world(double gravity);
void physics_destroy_world(int world);

int physics_create_fixed_plane(double pos_x, double pos_y, double pos_z, double width, double height);
//int physics_create_plane();
//int physics_create_rigdbody();
//void physics_destroy_object();

void physics_update(double time);

#endif

