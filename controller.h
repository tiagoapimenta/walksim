#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "interfaces.h"
#include "renderer.h"

class Controller : public Updateable, public Drawable, public Typeable
{
private:
	Renderer &render;
	double posX, posY, posZ, angleX, angleY;

public:
	Controller(Renderer &render);
	void close();

	void update(double time);
	void draw();
	void type(int key);
	void typeRelease(int key);
};

#endif

