#include "environment.h"
#include "sys/physics.h"
#include "sys/graphics.h"

#include <iostream>

Environment::Environment(double gravity)
{
	world = physics_create_world(-gravity);
	plane = physics_create_fixed_plane(world, 0.0, -10.0, 0.0, 20.0, 20.0);
}

void Environment::close()
{
	physics_destroy_world(world);
}

void Environment::draw()
{
	graphics_color(255, 255, 255);
	//Vertex position = physics_get_position(plane);
	//graphics_translate(position.x, position.y, position.z);
	Vertex vertices[6];
	std::cout << "----------" << std::endl;
	int triangles = physics_get_triangles(plane, vertices, 2);
	for (int i = 0; i < 1; i++)
	{
		std::cout << "(" << vertices[i].x << "x" << vertices[i].y << "x" << vertices[i].z << ")" << std::endl;
	}
	graphics_draw_triangles(vertices, triangles);
}

