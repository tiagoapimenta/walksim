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
	Renderer    render(env, doll, sim);

	render.init(argc, argv, SCREEN_WIDTH, SCREEN_HEIGHT);

	env.destroy();

	std::cout << "End." << std::endl;
	return 0;
}
