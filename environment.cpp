#include "environment.h"
#include "sys/physics.h"

Environment::Environment(double gravity)
{
	world = physics_create_world(-gravity);
	int plane = physics_create_fixed_plane(0.0, -10.0, 0.0, 20.0, 20.0);
}

void Environment::close()
{
	physics_destroy_world(world);
}

void Environment::draw()
{
	//draw plane
}

