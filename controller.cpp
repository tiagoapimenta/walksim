#include "controller.h"
#include "sys/physics.h"
#include "sys/graphics.h"

#include <iostream>

#define MOVE_STEP 0.5
#define VIEW_STEP 0.5

Controller::Controller(Renderer &render, Ragdoll &doll) : render(render), doll(doll), posX(0.0), posY(0.0), posZ(-20.0), angleX(0.0), angleY(0.0), time_count(0.0), state(-1)
{
	joints = doll.getJoints();

	for (int i = 0; i < JOINT_MAX; i++) {
		ks[i] = 300.0;
		kd[i] = 30.0;  
		target[i] = 0;
	}

	target[0] = -1.0 * DEFAULT_SIZE; 
	target[1] =  0.5 * DEFAULT_SIZE; 
	target[2] =  1.0 * DEFAULT_SIZE; 
}

void Controller::close()
{
}


void Controller::update(double time)
{
	time_count += time;

	int new_state = ((int)(time_count / 1.5)) % 4;

	if (new_state != state)
	{
		state = new_state;
		std::cout << "State " << state << std::endl;

		if (state % 2 == 0)
		{
			int leg1 = state / 2;
			int leg2 = 1 - leg1;
			target[leg1]     = -1.0 * DEFAULT_SIZE;
			target[leg2]     =  0.5 * DEFAULT_SIZE;
			target[leg1 + 2] =  1.0 * DEFAULT_SIZE;
			target[leg2 + 2] = -0.1 * DEFAULT_SIZE;
			target[leg1 + 4] =  0.0 * DEFAULT_SIZE;
			target[leg2 + 4] = -0.1 * DEFAULT_SIZE;
		}
		else
		{
			int leg1 = state / 2;
			int leg2 = 1 - leg1;
			target[leg1]     = -0.2 * DEFAULT_SIZE;
			target[leg2]     =  0.0 * DEFAULT_SIZE;
			target[leg1 + 2] =  0.2 * DEFAULT_SIZE;
			target[leg2 + 2] =  0.0 * DEFAULT_SIZE;
			target[leg1 + 4] =  0.1 * DEFAULT_SIZE;
			target[leg2 + 4] =  0.0 * DEFAULT_SIZE;
		}
	}

	for (int i = 0; i < JOINT_MAX; i++)
	{
		double limit = ks[i];

		double theta = physics_get_hinge_angle(joints[i]);
		double theta_rate = physics_get_hinge_angle_rate(joints[i]);
		double torque = ks[i] * (target[i] - theta) - kd[i] * theta_rate;

		if (torque > limit) torque = limit; 
		if (torque < -limit) torque = -limit; 

		physics_add_hinge_torque(joints[i], torque);
	}
}

void Controller::draw()
{
	graphics_rotate(angleX, angleY, 0.0);
	graphics_translate(posX, posY, posZ);
}

void Controller::type(int key)
{
	switch (key)
	{
		case KEY_ESCAPE:
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
		case 'z':
		{
			posY -= MOVE_STEP;
			break;
		}
		case 'x':
		{
			posY += MOVE_STEP;
			break;
		}
		case KEY_UP:
		{
			angleX -= VIEW_STEP;
			break;
		}
		case KEY_DOWN:
		{
			angleX += VIEW_STEP;
			break;
		}
		case KEY_LEFT:
		{
			angleY -= VIEW_STEP;
			break;
		}
		case KEY_RIGHT:
		{
			angleY += VIEW_STEP;
			break;
		}
	}
}

void Controller::typeRelease(int key)
{
}

