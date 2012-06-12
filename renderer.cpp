#include "renderer.h"
#include "sys/graphics.h"

static void update_callback(double time);

Renderer::Renderer(int argc, char **argv, int width, int height, Environment &env, Ragdoll &doll, Simulator &sim) : env(env), doll(doll), sim(sim)
{
	graphics_init(argc, argv);
	graphics_create_window("Walking Simulator", 100, 100, width, height);
}

void Renderer::close()
{
	graphics_close();
}

void Renderer::init(double time)
{
	graphics_set_updater(time, &update_callback);
	//graphics_set_typer();

	graphics_main_loop();
}

static void update_callback(double time)
{
	// call update
	// call draw
}

