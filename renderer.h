#ifndef RENDERER_H
#define RENDERER_H

#include <list>

#include "interfaces.h"

class Renderer
{
private:
	static std::list<Updateable*> updaters;
	static std::list<Drawable*> drawers;
	static std::list<Typeable*> typers;

	static void update_callback(double time);
	static void type_callback(int key);

public:
	Renderer(int argc, char **argv, int width, int height);
	void close();

	void init(double time);
	void addUpdater(Updateable &updater);
	void addDrawer(Drawable &drawer);
	void addTyper(Typeable &typer);
};

#endif

