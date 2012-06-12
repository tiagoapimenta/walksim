#include <vector>

#include <ode/ode.h>

#include "physics.h"

typedef struct
{
	dWorldID world;
	dSpaceID space;
	dJointGroupID contact_group;
} physics_world;


void physics_init()
{
	//dInitODE();
}

void physics_close()
{
	//dCloseODE();
}


int physics_create_world(double gravity)
{
	return 0;
}

void physics_destroy_world(int world)
{
}


int physics_create_fixed_plane(double pos_x, double pos_y, double pos_z, double width, double height)
{
	return 0;
}


void physics_update(double time)
{
}

