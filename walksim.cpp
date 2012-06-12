#include <iostream>

#include "defs.h"
#include "controller.h"
#include "renderer.h"

int main(int argc, char *argv[])
{
	std::cout << "Walking Simulation." << std::endl;

	Environment env(GRAVITY);
	Ragdoll     doll(env);
	Controller  control(env, doll);
	Simulator   sim(env, doll);
	Renderer    render(argc, argv, SCREEN_WIDTH, SCREEN_HEIGHT, env, doll, sim);

	//render.addController(control);
	//render.addUpdater(sim);
	//render.addDrawer(env);
	//render.addDrawer(doll);

	render.init(TIME_PER_FRAME);

	env.close();
	//doll.close();
	//control.close();
	//sim.close();
	render.close();

	std::cout << "End." << std::endl;
	return 0;
}
