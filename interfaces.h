#ifndef INTERFACES_H
#define INTERFACES_H

class Drawable
{
public:
	virtual void draw() = 0;
};

class Updateable
{
public:
	virtual void update(double time) = 0;
};

class Controllable : Drawable, Updateable
{
};

class Typeable
{
public:
	virtual void type(int key) = 0;
};

#endif

