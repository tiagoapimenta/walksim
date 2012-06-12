#include "simulator.h"
#include "sys/physics.h"

Simulator::Simulator(Environment &env, Ragdoll &doll) : env(env), doll(doll)
{
}


void Simulator::update(double time)
{
	physics_update(time);
}

