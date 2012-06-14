#include "ragdoll.h"
#include "sys/physics.h"
#include "sys/graphics.h"

#define DEFAULT_SIZE   10.0
#define DEFAULT_WIDTH  (0.04 * DEFAULT_SIZE)
#define DEFAULT_HEIGHT (0.2 * DEFAULT_SIZE)
#define DEFAULT_LENGTH (1e-6 * DEFAULT_SIZE)
#define DEFAULT_MASS   1.0

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

#define TORSO_X        0.0
#define TORSO_Y        (0.5 * TORSO_HEIGHT + THIGH_LENGTH + SHIN_LENGTH + 0.5 * DEFAULT_WIDTH)
#define TORSO_Z        0.0

#define LEFT_THIGH_X   0.0
#define LEFT_THIGH_Y   (TORSO_Y - 0.5 * TORSO_HEIGHT - 0.5 * THIGH_HEIGHT)
#define LEFT_THIGH_Z   0.0

#define RIGHT_THIGH_X  0.0
#define RIGHT_THIGH_Y  LEFT_THIGH_Y
#define RIGHT_THIGH_Z  0.0

#define LEFT_SHIN_X    0.0
#define LEFT_SHIN_Y    (TORSO_Y - 0.5 * TORSO_HEIGHT - THIGH_HEIGHT - 0.5 * SHIN_HEIGHT)
#define LEFT_SHIN_Z    0.0

#define RIGHT_SHIN_X   0.0
#define RIGHT_SHIN_Y   LEFT_SHIN_Y
#define RIGHT_SHIN_Z   0.0

#define LEFT_FOOT_X    (FOOT_WIDTH / 2)
#define LEFT_FOOT_Y    (TORSO_Y - 0.5 * TORSO_HEIGHT - THIGH_HEIGHT - SHIN_HEIGHT)
#define LEFT_FOOT_Z    0.0

#define RIGHT_FOOT_X   LEFT_FOOT_X
#define RIGHT_FOOT_Y   LEFT_FOOT_Y
#define RIGHT_FOOT_Z   0.0


Ragdoll::Ragdoll(Environment &env) : env(env)
{
	world = env.getWorld();

	object_list[0] = torso = physics_create_box(
		world,
		TORSO_X, TORSO_Y, TORSO_Z,
		TORSO_WIDTH, TORSO_HEIGHT, TORSO_LENGTH,
		TORSO_MASS
	);

	object_list[1] = left_thigh = physics_create_box(
		world,
		LEFT_THIGH_X, LEFT_THIGH_Y, LEFT_THIGH_Z,
		THIGH_WIDTH, THIGH_HEIGHT, THIGH_LENGTH,
		THIGH_MASS
	);

	object_list[2] = right_thigh = physics_create_box(
		world,
		RIGHT_THIGH_X, RIGHT_THIGH_Y, RIGHT_THIGH_Z,
		THIGH_WIDTH, THIGH_HEIGHT, THIGH_LENGTH,
		THIGH_MASS
	);

	object_list[3] = left_shin = physics_create_box(
		world,
		LEFT_SHIN_X, LEFT_SHIN_Y, LEFT_SHIN_Z,
		SHIN_WIDTH, SHIN_HEIGHT, SHIN_LENGTH,
		SHIN_MASS
	);

	object_list[4] = right_shin = physics_create_box(
		world,
		RIGHT_SHIN_X, RIGHT_SHIN_Y, RIGHT_SHIN_Z,
		SHIN_WIDTH, SHIN_HEIGHT, SHIN_LENGTH,
		SHIN_MASS
	);

	object_list[5] = left_foot = physics_create_box(
		world,
		LEFT_FOOT_X, LEFT_FOOT_Y, LEFT_FOOT_Z,
		FOOT_WIDTH, FOOT_HEIGHT, FOOT_LENGTH,
		FOOT_MASS
	);

	object_list[6] = right_foot = physics_create_box(
		world,
		RIGHT_FOOT_X, RIGHT_FOOT_Y, RIGHT_FOOT_Z,
		FOOT_WIDTH, FOOT_HEIGHT, FOOT_LENGTH,
		FOOT_MASS
	);
}

void Ragdoll::close()
{
	for (int i = 0 ; i < 7; i++)
	{
		physics_destroy_object(object_list[i]);
	}
}


void Ragdoll::draw()
{
	for (int i = 0 ; i < 7; i++)
	{
		Vertex lengths = physics_get_lengths(object_list[i]);
		Vertex position = physics_get_position(object_list[i]);
		Transform rotation = physics_get_rotation(object_list[i]);

		graphics_color(255, 255, 255);
		graphics_draw_box(position, rotation, lengths);
	}
}

