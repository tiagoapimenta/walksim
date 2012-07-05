#include "ragdoll.h"
#include "sys/physics.h"
#include "sys/graphics.h"

#include <iostream> // TODO: Temp

#define TORSO_WIDTH    DEFAULT_WIDTH
#define TORSO_HEIGHT   (0.480 * DEFAULT_SIZE)
#define TORSO_LENGTH   DEFAULT_LENGTH
#define TORSO_MASS     (7.0 * DEFAULT_MASS)

#define THIGH_WIDTH    DEFAULT_WIDTH
#define THIGH_HEIGHT   (0.45 * DEFAULT_SIZE)
#define THIGH_LENGTH   DEFAULT_LENGTH
#define THIGH_MASS     (5.0 * DEFAULT_MASS)

#define SHIN_WIDTH     DEFAULT_WIDTH
#define SHIN_HEIGHT    (0.4 * DEFAULT_SIZE)
#define SHIN_LENGTH    DEFAULT_LENGTH
#define SHIN_MASS      (5.0 * DEFAULT_MASS)

#define FOOT_WIDTH     DEFAULT_HEIGHT
#define FOOT_HEIGHT    DEFAULT_WIDTH
#define FOOT_LENGTH    DEFAULT_LENGTH
#define FOOT_MASS      DEFAULT_MASS

#define JOINT_RADIUS   (0.05 * DEFAULT_SIZE)

#define TORSO_X        0.0
#define TORSO_Y        (0.5 * TORSO_HEIGHT + THIGH_HEIGHT + SHIN_HEIGHT + FOOT_HEIGHT - 10.0)
#define TORSO_Z        0.0

#define LEFT_THIGH_X   0.0
#define LEFT_THIGH_Y   (TORSO_Y - 0.5 * TORSO_HEIGHT - 0.5 * THIGH_HEIGHT)
#define LEFT_THIGH_Z   DEFAULT_LENGTH

#define RIGHT_THIGH_X  0.0
#define RIGHT_THIGH_Y  LEFT_THIGH_Y
#define RIGHT_THIGH_Z  (-DEFAULT_LENGTH)

#define LEFT_SHIN_X    0.0
#define LEFT_SHIN_Y    (TORSO_Y - 0.5 * TORSO_HEIGHT - THIGH_HEIGHT - 0.5 * SHIN_HEIGHT)
#define LEFT_SHIN_Z    DEFAULT_LENGTH

#define RIGHT_SHIN_X   0.0
#define RIGHT_SHIN_Y   LEFT_SHIN_Y
#define RIGHT_SHIN_Z   (-DEFAULT_LENGTH)

#define LEFT_FOOT_X    (FOOT_WIDTH / 2)
#define LEFT_FOOT_Y    (TORSO_Y - 0.5 * TORSO_HEIGHT - THIGH_HEIGHT - SHIN_HEIGHT)
#define LEFT_FOOT_Z    DEFAULT_LENGTH

#define RIGHT_FOOT_X   LEFT_FOOT_X
#define RIGHT_FOOT_Y   LEFT_FOOT_Y
#define RIGHT_FOOT_Z   (-DEFAULT_LENGTH)


#define DEFAULT_AXIS_X 0.0
#define DEFAULT_AXIS_Y 0.0
#define DEFAULT_AXIS_Z 1.0

#define LEFT_HIP_X     0.0
#define LEFT_HIP_Y     (TORSO_Y - 0.5 * TORSO_HEIGHT)
#define LEFT_HIP_Z     DEFAULT_LENGTH

#define RIGHT_HIP_X    0.0
#define RIGHT_HIP_Y    LEFT_HIP_Y
#define RIGHT_HIP_Z    (-DEFAULT_LENGTH)

#define LEFT_KNEE_X    0.0
#define LEFT_KNEE_Y    (TORSO_Y - 0.5 * TORSO_HEIGHT - THIGH_HEIGHT)
#define LEFT_KNEE_Z    DEFAULT_LENGTH

#define RIGHT_KNEE_X   0.0
#define RIGHT_KNEE_Y   LEFT_KNEE_Y
#define RIGHT_KNEE_Z   (-DEFAULT_LENGTH)

#define LEFT_ANKLE_X   0.0
#define LEFT_ANKLE_Y   (TORSO_Y - 0.5 * TORSO_HEIGHT - THIGH_HEIGHT - SHIN_HEIGHT)
#define LEFT_ANKLE_Z   DEFAULT_LENGTH

#define RIGHT_ANKLE_X  0.0
#define RIGHT_ANKLE_Y  LEFT_ANKLE_Y
#define RIGHT_ANKLE_Z  (-DEFAULT_LENGTH)


#define STEP_INTERVAL  0.8


Ragdoll::Ragdoll(Environment &env) : env(env), time_count(0.0), ground(-1), state(-1), new_state(0)
{
	world = env.getWorld();
	ground = env.getGround();

	objects[OBJECT_TORSO] = physics_create_box(
		world,
		TORSO_X, TORSO_Y, TORSO_Z,
		TORSO_WIDTH, TORSO_HEIGHT, TORSO_LENGTH,
		TORSO_MASS
	);

	objects[OBJECT_LEFT_THIGH] = physics_create_box(
		world,
		LEFT_THIGH_X, LEFT_THIGH_Y, LEFT_THIGH_Z,
		THIGH_WIDTH, THIGH_HEIGHT, THIGH_LENGTH,
		THIGH_MASS
	);

	objects[OBJECT_RIGHT_THIGH] = physics_create_box(
		world,
		RIGHT_THIGH_X, RIGHT_THIGH_Y, RIGHT_THIGH_Z,
		THIGH_WIDTH, THIGH_HEIGHT, THIGH_LENGTH,
		THIGH_MASS
	);

	objects[OBJECT_LEFT_SHIN] = physics_create_box(
		world,
		LEFT_SHIN_X, LEFT_SHIN_Y, LEFT_SHIN_Z,
		SHIN_WIDTH, SHIN_HEIGHT, SHIN_LENGTH,
		SHIN_MASS
	);

	objects[OBJECT_RIGHT_SHIN] = physics_create_box(
		world,
		RIGHT_SHIN_X, RIGHT_SHIN_Y, RIGHT_SHIN_Z,
		SHIN_WIDTH, SHIN_HEIGHT, SHIN_LENGTH,
		SHIN_MASS
	);

	objects[OBJECT_LEFT_FOOT] = physics_create_box(
		world,
		LEFT_FOOT_X, LEFT_FOOT_Y, LEFT_FOOT_Z,
		FOOT_WIDTH, FOOT_HEIGHT, FOOT_LENGTH,
		FOOT_MASS
	);

	objects[OBJECT_RIGHT_FOOT] = physics_create_box(
		world,
		RIGHT_FOOT_X, RIGHT_FOOT_Y, RIGHT_FOOT_Z,
		FOOT_WIDTH, FOOT_HEIGHT, FOOT_LENGTH,
		FOOT_MASS
	);


	joints[JOINT_LEFT_HIP] = physics_create_hinge_joint(
		world,
		objects[OBJECT_TORSO], objects[OBJECT_LEFT_THIGH],
		LEFT_HIP_X, LEFT_HIP_Y, LEFT_HIP_Z,
		DEFAULT_AXIS_X, DEFAULT_AXIS_Y, DEFAULT_AXIS_Z
	);

	joints[JOINT_RIGHT_HIP] = physics_create_hinge_joint(
		world,
		objects[OBJECT_TORSO], objects[OBJECT_RIGHT_THIGH],
		RIGHT_HIP_X, RIGHT_HIP_Y, RIGHT_HIP_Z,
		DEFAULT_AXIS_X, DEFAULT_AXIS_Y, DEFAULT_AXIS_Z
	);

	joints[JOINT_LEFT_KNEE] = physics_create_hinge_joint(
		world,
		objects[OBJECT_LEFT_THIGH], objects[OBJECT_LEFT_SHIN],
		LEFT_KNEE_X, LEFT_KNEE_Y, LEFT_KNEE_Z,
		DEFAULT_AXIS_X, DEFAULT_AXIS_Y, DEFAULT_AXIS_Z
	);

	joints[JOINT_RIGHT_KNEE] = physics_create_hinge_joint(
		world,
		objects[OBJECT_RIGHT_THIGH], objects[OBJECT_RIGHT_SHIN],
		RIGHT_KNEE_X, RIGHT_KNEE_Y, RIGHT_KNEE_Z,
		DEFAULT_AXIS_X, DEFAULT_AXIS_Y, DEFAULT_AXIS_Z
	);

	joints[JOINT_LEFT_ANKLE] = physics_create_hinge_joint(
		world,
		objects[OBJECT_LEFT_SHIN], objects[OBJECT_LEFT_FOOT],
		LEFT_ANKLE_X, LEFT_ANKLE_Y, LEFT_ANKLE_Z,
		DEFAULT_AXIS_X, DEFAULT_AXIS_Y, DEFAULT_AXIS_Z
	);

	joints[JOINT_RIGHT_ANKLE] = physics_create_hinge_joint(
		world,
		objects[OBJECT_RIGHT_SHIN], objects[OBJECT_RIGHT_FOOT],
		RIGHT_ANKLE_X, RIGHT_ANKLE_Y, RIGHT_ANKLE_Z,
		DEFAULT_AXIS_X, DEFAULT_AXIS_Y, DEFAULT_AXIS_Z
	);

	for (int i = 0; i < JOINT_LEFT_ANKLE; i++) {
		ks[i]     = 2000.0;
		kd[i]     =  200.0;  
		target[i] =    0.0;
	}

	ks[JOINT_LEFT_ANKLE]      = 500.0;
	kd[JOINT_LEFT_ANKLE]      =  50.0;  
	target[JOINT_LEFT_ANKLE]  =   0.0;

	ks[JOINT_RIGHT_ANKLE]     = 500.0;
	kd[JOINT_RIGHT_ANKLE]     =  50.0;  
	target[JOINT_RIGHT_ANKLE] =   0.0;

	// target[0] = -1.0;
	// target[1] =  0.5;
	// target[2] =  1.0;
}

void Ragdoll::close()
{
	for (int i = 0 ; i < JOINT_MAX; i++)
	{
		physics_destroy_joint(joints[i]);
	}
	for (int i = 0 ; i < OBJECT_MAX; i++)
	{
		physics_destroy_object(objects[i]);
	}
}


void Ragdoll::draw()
{
	for (int i = OBJECT_MAX; i-- ;)
	{
		Vertex lengths = physics_get_lengths(objects[i]);
		Vertex position = physics_get_position(objects[i]);
		Transform rotation = physics_get_rotation(objects[i]);

		if (i == 0) graphics_color(255, 255, 0);
		else if (i % 2 == 0) graphics_color(78, 78, 156);
		else graphics_color(78, 156, 78);
		graphics_draw_box(position, rotation, lengths);
	}

	for (int i = 0; i < JOINT_MAX; i++)
	{
		Vertex position = physics_get_hinge_anchor(joints[i]);

		graphics_color(255, 0, 255);
		graphics_draw_sphere(position, JOINT_RADIUS);
	}
}

void Ragdoll::update(double time)
{
	if (state % 2 == 0)
	{
		time_count += time;

		if (time_count > STEP_INTERVAL)
		{
			new_state = state + 1;
			time_count -= STEP_INTERVAL;
		}
	}

	if (new_state % 4 != state)
	{
		state = new_state % 4;
		std::cout << "State " << state << std::endl;

		if (state % 3 == 0)
		{
			int leg1 = state / 2;
			int leg2 = 1 - leg1;
			target[leg1]     = -0.5; // hip
			target[leg2]     =  0.2; // hip
			target[leg1 + 2] =  1.5; // knee
			target[leg2 + 2] =  0.5; // knee
			target[leg1 + 4] = -0.5; // ankle
			target[leg2 + 4] = -0.5; // ankle
		}
		else
		{
			int leg1 = state / 2;
			int leg2 = 1 - leg1;
			target[leg1]     = -0.4; // hip
			target[leg2]     =  0.3; // hip
			target[leg1 + 2] =  1.5; // knee
			target[leg2 + 2] =  0.5; // knee
			target[leg1 + 4] = -0.5; // ankle
			target[leg2 + 4] = -0.5; // ankle
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


int* Ragdoll::getJoints()
{
	return joints;
}


void Ragdoll::collide(int objectA, int objectB)
{
	if (objectA != ground && objectB != ground) return;

	int object_foot = (objectA == ground) ? objectB : objectA;

	if (state == 1 && object_foot == objects[OBJECT_LEFT_FOOT]) new_state = state + 1;
	else if (state == 3 && object_foot == objects[OBJECT_RIGHT_FOOT]) new_state = state + 1;
}

