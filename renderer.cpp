#include "renderer.h"
#include "sys/graphics.h"

std::list<Updateable*> Renderer::updaters;
std::list<Drawable*> Renderer::drawers;
std::list<Typeable*> Renderer::typers;

Renderer::Renderer(int argc, char **argv, int width, int height)
{
	graphics_init(argc, argv);
	graphics_create_window("Walking Simulator", 100, 100, width, height);
}

void Renderer::close()
{
	updaters.clear();
	drawers.clear();
	typers.clear();
	graphics_close();
}

void Renderer::init(double time)
{
	graphics_set_updater(time, &update_callback);
	graphics_set_typer(&type_callback);

	graphics_main_loop();
}

void Renderer::addUpdater(Updateable &updater)
{
	updaters.push_back(&updater);
}

void Renderer::addDrawer(Drawable &drawer)
{
	drawers.push_back(&drawer);
}

void Renderer::addTyper(Typeable &typer)
{
	typers.push_back(&typer);
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

void Renderer::type_callback(int key)
{
	for (std::list<Typeable*>::iterator it = typers.begin(); it != typers.end(); it++)
	{
		(*it)->type(key);
	}
}

