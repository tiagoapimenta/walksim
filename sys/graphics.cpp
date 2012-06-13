#include <map>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include "graphics.h"
#include "microtime.h"

static mtime last_time = 0;
static double update_time = 0.0;
static void(*update_func)(double time) = NULL;
static void(*type_func)(int key) = NULL;

static void on_close();
static void on_resize(int width, int height);
static void on_keypress(unsigned char key, int x, int y);
static void on_update();


void graphics_init(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glShadeModel(GL_FLAT);
}

void graphics_close()
{
}


int graphics_create_window(const char *title, int left, int top, int width, int height)
{
	glutInitWindowSize(width, height);
	glutInitWindowPosition(left, top);

	int window_id = glutCreateWindow(title);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutCloseFunc(on_close);
	glutReshapeFunc(on_resize);
	glutKeyboardFunc(on_keypress);
	glutIdleFunc(on_update);

	return window_id;
}

void graphics_destroy_window(int window)
{
	glutDestroyWindow(window);
}


void graphics_set_updater(double update_interval, void(*updater)(double time))
{
	update_time = update_interval;
	update_func = updater;
}

void graphics_set_typer(void(*typer)(int key))
{
	type_func = typer;
}


void graphics_main_loop()
{
	last_time = microtime();
	glutMainLoop();
}


void graphics_color(unsigned char red, unsigned char green, unsigned char blue)
{
	glColor3d(red / 255.0, green / 255.0, blue / 255.0);
}


void graphics_draw_triangles(Vertex *vertices, int triangles)
{
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < triangles * 3; i++)
	{
		glVertex3d(vertices[i].x, vertices[i].y, vertices[i].z);
	}
	glEnd();
	glPopMatrix();
}


static void on_close()
{
	glutLeaveMainLoop();
}

static void on_resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

static void on_keypress(unsigned char key, int x, int y)
{
	if (type_func) type_func(key);
}

static void on_update()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	mtime elapsed_time = 0;
	mtime time_per_frame = 0;

	if (update_time)
	{
		if (update_func) update_func(update_time);
		glutSwapBuffers();

		time_per_frame = update_time * 1000;
		elapsed_time = microtime() - last_time;
	}
	else
	{
		time_per_frame = elapsed_time = microtime() - last_time;

		if (update_func) update_func(time_per_frame / 1000.0);
		glutSwapBuffers();
	}

	if (elapsed_time < time_per_frame) microsleep(time_per_frame - elapsed_time);
	else if (elapsed_time != time_per_frame) std::cerr << "Overlap-time of " << (elapsed_time - time_per_frame) << " milliseconds." << std::endl;

	last_time += time_per_frame;
}

