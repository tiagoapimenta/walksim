#ifndef RENDERER_H
#define RENDERER_H

#include <list>

#include "ragdoll.h"
#include "simulator.h"
#include "interfaces.h"

class Renderer
{
private:
	Environment &env;
	Ragdoll &doll;
	Simulator &sim;
	static std::list<Updateable*> updaters;
	static std::list<Drawable*> drawers;

	static void update_callback(double time);

public:
	Renderer(int argc, char **argv, int width, int height, Environment &env, Ragdoll &doll, Simulator &sim);
	void close();

	void init(double time);
	void addUpdater(Updateable &updater);
	void addDrawer(Drawable &drawer);
	void addController(Controllable &controller);
};

#endif

