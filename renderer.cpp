#include "renderer.h"
#include "sys/graphics.h"

std::list<Updateable*> Renderer::updaters;
std::list<Drawable*> Renderer::drawers;

//void update_callback(double time);

Renderer::Renderer(int argc, char **argv, int width, int height, Environment &env, Ragdoll &doll, Simulator &sim) : env(env), doll(doll), sim(sim)
{
	graphics_init(argc, argv);
	graphics_create_window("Walking Simulator", 100, 100, width, height);
}

void Renderer::close()
{
	updaters.clear();
	drawers.clear();
	graphics_close();
}

void Renderer::init(double time)
{
	graphics_set_updater(time, &update_callback);
	//graphics_set_typer();

	graphics_main_loop();
}

void Renderer::addUpdater(Updateable &updater)
{
	updaters.push_back(&updater);
	updaters.unique();
}

void Renderer::addDrawer(Drawable &drawer)
{
	drawers.push_back(&drawer);
	drawers.unique();
}

void Renderer::addController(Controllable &controller)
{
	updaters.push_back((Updateable*)&controller);
	drawers.push_back((Drawable*)&controller);
	updaters.unique();
	drawers.unique();
}


void Renderer::update_callback(double time)
{
	for (std::list<Updateable*>::iterator it = updaters.begin(); it != updaters.end(); it++)
	{
		(*it)->update(time);
	}
	for (std::list<Drawable*>::iterator it = drawers.begin(); it != drawers.end(); it++)
	{
		(*it)->draw();
	}
}

