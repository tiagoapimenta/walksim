#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "interfaces.h"

class Environment : public Drawable
{
private:
	int world;

public:
	Environment(double gravity);
	void close();

	void draw();
};

#endif

