#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <list>

#include "interfaces.h"

class Simulator : public Updateable
{
private:
	static std::list<Collideable*> colliders;

	static void collide_callback(int objectA, int objectB);

public:
	Simulator();
	void close();

	void update(double time);
	void addCollider(Collideable &collider);
};

#endif

