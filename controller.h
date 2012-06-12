#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "interfaces.h"

class Controller : public Updateable, public Drawable, public Typeable
{
private:

public:
	Controller();
	void close();

	void update(double time);
	void draw();
	void type(int key);
};

#endif

