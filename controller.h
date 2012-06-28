#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "interfaces.h"
#include "renderer.h"
#include "ragdoll.h"

class Controller : public Drawable, public Typeable
{
private:
	Renderer &render;
	double posX, posY, posZ, angleX, angleY;

public:
	Controller(Renderer &render);
	void close();

	void draw();
	void type(int key);
	void typeRelease(int key);
};

#endif

