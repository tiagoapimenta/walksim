#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "ragdoll.h"

class Simulator
{
private:
	Environment env;
	Ragdoll doll;

public:
	Simulator(Environment env, Ragdoll doll);
};

#endif

