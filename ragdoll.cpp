#include "ragdoll.h"
#include "sys/physics.h"
#include "sys/graphics.h"

#define DEFAULT_WIDTH  0.04
#define DEFAULT_HEIGHT 0.2
#define DEFAULT_LENGTH 1e-6
#define DEFAULT_MASS   1.0

#define TORSO_WIDTH    DEFAULT_WIDTH
#define TORSO_HEIGHT   0.480
#define TORSO_LENGTH   DEFAULT_LENGTH
#define TORSO_MASS     (7.0 * DEFAULT_MASS)

#define THIGH_WIDTH    DEFAULT_WIDTH
#define THIGH_HEIGHT   0.45
#define THIGH_LENGTH   DEFAULT_LENGTH
#define THIGH_MASS     (5.0 * DEFAULT_MASS)

#define SHIN_WIDTH     DEFAULT_WIDTH
#define SHIN_HEIGHT    0.4
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


Ragdoll::Ragdoll()
{
	
}

void Ragdoll::close()
{
	
}


void Ragdoll::draw()
{
	
}

