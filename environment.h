#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "interfaces.h"

class Environment : Drawable
{
private:
	int world;

public:
	Environment(double gravity);

	void draw();

	void destroy();
};

#endif

