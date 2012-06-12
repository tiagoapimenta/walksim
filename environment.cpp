#include "environment.h"
#include "sys/physics.h"

#include <iostream>

Environment::Environment(double gravity)
{
	physics_init();
	world = physics_create_world(-gravity);
	int plane = physics_create_fixed_plane(0.0, -10.0, 0.0, 20.0, 20.0);
}

void Environment::destroy()
{
	physics_destroy_world(world);
	physics_close();
}


void Environment::draw()
{
	//draw plane
}

