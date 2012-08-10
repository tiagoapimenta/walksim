Walking Simulator
=================

This project I made for a master degree class about advanced animation with
Leo Pini teacher <http://www.dca.fee.unicamp.br/~leopini/> during the first semester of 2012.

The purpose was make a humanoid character walking some steps.

Compiling
---------

You'll need OpenGL, GLU, GLUT and ODE libraries, if you're using Ubuntu or
other Debian based distribution the following command should work:

	# apt-get install -y build-essential mesa-common-dev freeglut3-dev libglu1-mesa-dev binutils-gold libgl1-mesa-dev libode-dev

Then you can try to compile the code:

	$ make
	$ ./walksim

For Windows you can use MSYS with MinGW or Cingwing, it should work as well,
but I didn't checked it, so perhaps you'll need to do some little changes, but
not so much.
