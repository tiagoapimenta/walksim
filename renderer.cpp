#include "renderer.h"
#include "sys/graphics.h"

Renderer::Renderer(int argc, char **argv, int width, int height, Environment &env, Ragdoll &doll, Simulator &sim) : env(env), doll(doll), sim(sim)
{
	graphics_init(argc, argv);
	window = graphics_create_window("Walking Simulator", 100, 100, width, height);
}

void Renderer::close()
{
	//graphics_destroy_window(window);
	graphics_close();
}

void Renderer::init(double time)
{
	//graphics_set_updater(time, ...);
	//graphics_set_typer();

	graphics_main_loop();
}

