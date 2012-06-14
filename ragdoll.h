#ifndef RAGDOLL_H
#define RAGDOLL_H

#include "interfaces.h"
#include "environment.h"

#define OBJECT_TORSO       0
#define OBJECT_LEFT_THIGH  1
#define OBJECT_RIGHT_THIGH 2
#define OBJECT_LEFT_SHIN   3
#define OBJECT_RIGHT_SHIN  4
#define OBJECT_LEFT_FOOT   5
#define OBJECT_RIGHT_FOOT  6
#define OBJECT_MAX         7

#define JOINT_LEFT_HIP     0
#define JOINT_RIGHT_HIP    1
#define JOINT_LEFT_KNEE    2
#define JOINT_RIGHT_KNEE   3
#define JOINT_LEFT_ANKLE   4
#define JOINT_RIGHT_ANKLE  5
#define JOINT_MAX          6


#define DEFAULT_SIZE   10.0
#define DEFAULT_WIDTH  (0.04 * DEFAULT_SIZE)
#define DEFAULT_HEIGHT (0.2 * DEFAULT_SIZE)
#define DEFAULT_LENGTH (0.1 * DEFAULT_SIZE) //(1e-6 * DEFAULT_SIZE)
#define DEFAULT_MASS   1.0


class Ragdoll : public Drawable
{
private:
	Environment &env;
	int world;
	int objects[OBJECT_MAX];
	int joints[JOINT_MAX];

public:
	Ragdoll(Environment &env);
	void close();

	void draw();

	int* getJoints();
};

#endif

