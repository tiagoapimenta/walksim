#include "controller.h"
#include "sys/graphics.h"

#define MOVE_STEP 0.5
#define VIEW_STEP 0.5

Controller::Controller(Renderer &render) : render(render), posX(0.0), posY(0.0), posZ(-20.0), angleX(0.0), angleY(0.0)
{
}

void Controller::close()
{
}


void Controller::update(double time)
{
	graphics_translate(posX, posY, posZ);
	graphics_rotate(angleX, angleY, 0.0);
}

void Controller::draw()
{
}

void Controller::type(int key)
{
	switch (key)
	{
		case 27:
		{
			render.closeWindow();
			break;
		}
		case 'w':
		{
			posZ += MOVE_STEP;
			break;
		}
		case 's':
		{
			posZ -= MOVE_STEP;
			break;
		}
		case 'a':
		{
			posX += MOVE_STEP;
			break;
		}
		case 'd':
		{
			posX -= MOVE_STEP;
			break;
		}
	}
}

