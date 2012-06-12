#include <map>

#include <ode/ode.h>

#include "physics.h"

typedef struct
{
	dWorldID world;
	dSpaceID space;
	dJointGroupID contact_group;
} World;

std::map<int, World> worlds;
int world_last_id = 0;


void physics_init()
{
	dInitODE();
}

void physics_close()
{
	dCloseODE();
}


int physics_create_world(double gravity)
{
	World world;
	world.world = dWorldCreate();
	world.space = dSimpleSpaceCreate(0);
	world.contact_group = dJointGroupCreate(0);
	dWorldSetGravity(world.world, 0.0, gravity, 0.0);

	worlds.insert(std::make_pair(world_last_id, world));
	return world_last_id++;
}

void physics_destroy_world(int world_id)
{
	World world = worlds.at(world_id);
	dJointGroupDestroy(world.contact_group);
	dSpaceDestroy(world.space);
	dWorldDestroy(world.world);

	worlds.erase(world_id);
}


int physics_create_fixed_plane(double pos_x, double pos_y, double pos_z, double width, double height)
{
	// TODO: create plane
	return 0;
}


void physics_update(double time)
{
	for (std::map<int, World>::iterator it = worlds.begin(); it != worlds.end(); it++)
	{
		dJointGroupEmpty(it->second.contact_group);
		//dSpaceCollide(it->second.space, 0, nearCallback);
		dWorldQuickStep(it->second.world, time);
	}
}

