#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "interfaces.h"
#include "renderer.h"
#include "ragdoll.h"

class Controller : public Updateable, public Drawable, public Typeable
{
private:
	Renderer &render;
	Ragdoll &doll;
	double posX, posY, posZ, angleX, angleY;
	int *joints;
	double ks[JOINT_MAX], kd[JOINT_MAX], target[JOINT_MAX];
	int state;
	double time_count;

public:
	Controller(Renderer &render, Ragdoll &doll);
	void close();

	void update(double time);
	void draw();
	void type(int key);
	void typeRelease(int key);
};

#endif

