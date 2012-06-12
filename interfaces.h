#ifndef INTERFACES_H
#define INTERFACES_H

class Drawable
{
public:
	void draw();
};

class Updateable
{
public:
	void update();
};

class Typeable
{
public:
	void type(int key);
};

#endif

