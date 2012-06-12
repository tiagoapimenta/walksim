#include "simulator.h"
#include "sys/physics.h"

Simulator::Simulator()
{
	physics_init();
}

void Simulator::close()
{
	physics_close();
}


void Simulator::update(double time)
{
	physics_update(time);
}

