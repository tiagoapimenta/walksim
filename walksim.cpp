#include <iostream>

#include "defs.h"
#include "renderer.h"
#include "simulator.h"
#include "environment.h"
#include "ragdoll.h"
#include "controller.h"

int main(int argc, char *argv[])
{
	std::cout << "Walking Simulation." << std::endl;

	Renderer    render(argc, argv, SCREEN_WIDTH, SCREEN_HEIGHT);
	Simulator   sim;
	Environment env(GRAVITY);
	Ragdoll     doll(env);
	Controller  control(render, doll);

	render.addUpdater(control);
	render.addUpdater(sim);
	render.addDrawer(control);
	render.addDrawer(env);
	render.addDrawer(doll);
	render.addTyper(control);

	render.init(TIME_PER_FRAME);

	control.close();
	doll.close();
	env.close();
	sim.close();
	render.close();

	std::cout << "End." << std::endl;
	return 0;
}
