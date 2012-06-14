#ifndef RAGDOLL_H
#define RAGDOLL_H

#include "interfaces.h"
#include "environment.h"

class Ragdoll : public Drawable
{
private:
	Environment &env;
	int world;
	int torso;
	int left_thigh;
	int right_thigh;
	int left_shin;
	int right_shin;
	int left_foot;
	int right_foot;
	int object_list[7];

public:
	Ragdoll(Environment &env);
	void close();

	void draw();
};

#endif

