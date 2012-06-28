#include "simulator.h"
#include "sys/physics.h"

std::list<Collideable*> Simulator::colliders;

Simulator::Simulator()
{
	physics_init();
	physics_set_collider(&collide_callback);
}

void Simulator::close()
{
	physics_close();
}


void Simulator::update(double time)
{
	physics_update(time);
}

void Simulator::addCollider(Collideable &collider)
{
	colliders.push_back(&collider);
}


void Simulator::collide_callback(int objectA, int objectB)
{
	for (std::list<Collideable*>::iterator it = colliders.begin(); it != colliders.end(); it++)
	{
		(*it)->collide(objectA, objectB);
	}
}
