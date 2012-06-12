#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "interfaces.h"

class Simulator : public Updateable
{
private:

public:
	Simulator();
	void close();

	void update(double time);
};

#endif

