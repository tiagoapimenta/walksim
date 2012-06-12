#ifndef RAGDOLL_H
#define RAGDOLL_H

#include "environment.h"

class Ragdoll
{
private:
	Environment &env;

public:
	Ragdoll(Environment &env);
};

#endif

