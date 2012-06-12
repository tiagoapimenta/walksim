#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ragdoll.h"

class Controller
{
private:
	Environment &env;
	Ragdoll &doll;

public:
	Controller(Environment &env, Ragdoll &doll);
};

#endif

