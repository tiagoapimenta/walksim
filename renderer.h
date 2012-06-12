#ifndef RENDERER_H
#define RENDERER_H

#include "ragdoll.h"
#include "simulator.h"

class Renderer
{
private:
	Environment &env;
	Ragdoll &doll;
	Simulator &sim;
	int window;

public:
	Renderer(int argc, char **argv, int width, int height, Environment &env, Ragdoll &doll, Simulator &sim);
	void close();

	void init(double time);
};

#endif

