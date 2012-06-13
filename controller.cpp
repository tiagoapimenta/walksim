#include "controller.h"

Controller::Controller(Renderer &render) : render(render)
{
}

void Controller::close()
{
}


void Controller::update(double time)
{
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
	}
}

