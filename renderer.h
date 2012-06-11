#ifndef RENDERER_H
#define RENDERER_H

#include "ragdoll.h"
#include "simulator.h"

class Renderer
{
private:
	Environment env;
	Ragdoll doll;
	Simulator sim;

public:
	Renderer(Environment env, Ragdoll doll, Simulator sim);

	void init(int argc, char **argv, int width, int height);
};

#endif

