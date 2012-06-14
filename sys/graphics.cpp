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
static void(*type_release_func)(int key) = NULL;
static bool key_state[3] = {false, false, false};

static void on_close();
static void on_resize(int width, int height);
static void on_keydown(unsigned char key, int x, int y);
static void on_keyup(unsigned char key, int x, int y);
static void on_specialdown(int key, int x, int y);
static void on_specialup(int key, int x, int y);
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
	// Hint: use glutSetKeyRepeat(0) to key statefull

	glutCloseFunc(on_close);
	glutReshapeFunc(on_resize);
	glutKeyboardFunc(on_keydown);
	glutKeyboardUpFunc(on_keyup);
	glutSpecialFunc(on_specialdown);
	glutSpecialUpFunc(on_specialup);
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

void graphics_set_typer_release(void(*typer)(int key))
{
	type_release_func = typer;
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

void graphics_draw_box(Vertex position, Transform rotation, Vertex lengths)
{
	//glEnable(GL_LIGHTING);
	//glShadeModel(GL_FLAT);
	double matrix[4][4];
	matrix[0][0] = rotation.matrix[0][0];
	matrix[0][1] = rotation.matrix[1][0];
	matrix[0][2] = rotation.matrix[2][0];
	matrix[0][3] = 0.0;
	matrix[1][0] = rotation.matrix[0][1];
	matrix[1][1] = rotation.matrix[1][1];
	matrix[1][2] = rotation.matrix[2][1];
	matrix[1][3] = 0.0;
	matrix[2][0] = rotation.matrix[0][2];
	matrix[2][1] = rotation.matrix[1][2];
	matrix[2][2] = rotation.matrix[2][2];
	matrix[2][3] = 0.0;
	matrix[3][0] = position.x;
	matrix[3][1] = position.y;
	matrix[3][2] = position.z;
	matrix[3][3] = 1.0;

	glPushMatrix();
	glMultMatrixd((double*)matrix);

	double half_x = lengths.x / 2;
	double half_y = lengths.y / 2;
	double half_z = lengths.z / 2;

	glBegin(GL_TRIANGLE_STRIP); // Sides
	glNormal3d(-1.0, 0.0, 0.0);
	glVertex3d(-half_x, -half_y, -half_z);
	glVertex3d(-half_x, -half_y,  half_z);
	glVertex3d(-half_x,  half_y, -half_z);
	glVertex3d(-half_x,  half_y,  half_z);
	glNormal3d(0.0, 1.0, 0.0);
	glVertex3d( half_x,  half_y, -half_z);
	glVertex3d( half_x,  half_y,  half_z);
	glNormal3d(1.0, 0.0, 0.0);
	glVertex3d( half_x, -half_y, -half_z);
	glVertex3d( half_x, -half_y,  half_z);
	glNormal3d(0,-1,0);
	glVertex3d(-half_x, -half_y, -half_z);
	glVertex3d(-half_x, -half_y,  half_z);
	glEnd();

	glBegin(GL_TRIANGLE_FAN); // Top Face
	glNormal3d(0.0, 0.0, 1.0);
	glVertex3d(-half_x, -half_y,  half_z);
	glVertex3d( half_x, -half_y,  half_z);
	glVertex3d( half_x,  half_y,  half_z);
	glVertex3d(-half_x,  half_y,  half_z);
	glEnd();

	glBegin(GL_TRIANGLE_FAN); // Bottom Face
	glNormal3d(0.0, 0.0, -1.0);
	glVertex3d(-half_x, -half_y, -half_z);
	glVertex3d(-half_x,  half_y, -half_z);
	glVertex3d( half_x,  half_y, -half_z);
	glVertex3d( half_x, -half_y, -half_z);
	glEnd();

	glPopMatrix();
}


void graphics_translate(double x, double y, double z)
{
	glTranslated(x, y, z);
}

void graphics_rotate(double x, double y, double z)
{
	if (x) glRotated(x, 1.0, 0.0, 0.0);
	if (y) glRotated(y, 0.0, 1.0, 0.0);
	if (z) glRotated(z, 0.0, 0.0, 1.0);
}

void graphics_scale(double x, double y, double z)
{
	glScaled(x, y, z);
}



static int translate_key(unsigned char key)
{
	int translated_key = 0;
	switch (key)
	{
		case GLUT_KEY_F1:
		{
			translated_key = KEY_F1;
			break;
		}
		case GLUT_KEY_F2:
		{
			translated_key = KEY_F2;
			break;
		}
		case GLUT_KEY_F3:
		{
			translated_key = KEY_F3;
			break;
		}
		case GLUT_KEY_F4:
		{
			translated_key = KEY_F4;
			break;
		}
		case GLUT_KEY_F5:
		{
			translated_key = KEY_F5;
			break;
		}
		case GLUT_KEY_F6:
		{
			translated_key = KEY_F6;
			break;
		}
		case GLUT_KEY_F7:
		{
			translated_key = KEY_F7;
			break;
		}
		case GLUT_KEY_F8:
		{
			translated_key = KEY_F8;
			break;
		}
		case GLUT_KEY_F9:
		{
			translated_key = KEY_F9;
			break;
		}
		case GLUT_KEY_F10:
		{
			translated_key = KEY_F10;
			break;
		}
		case GLUT_KEY_F11:
		{
			translated_key = KEY_F11;
			break;
		}
		case GLUT_KEY_F12:
		{
			translated_key = KEY_F12;
			break;
		}
		case GLUT_KEY_LEFT:
		{
			translated_key = KEY_LEFT;
			break;
		}
		case GLUT_KEY_UP:
		{
			translated_key = KEY_UP;
			break;
		}
		case GLUT_KEY_RIGHT:
		{
			translated_key = KEY_RIGHT;
			break;
		}
		case GLUT_KEY_DOWN:
		{
			translated_key = KEY_DOWN;
			break;
		}
		case GLUT_KEY_PAGE_UP:
		{
			translated_key = KEY_PAGE_UP;
			break;
		}
		case GLUT_KEY_PAGE_DOWN:
		{
			translated_key = KEY_PAGE_DOWN;
			break;
		}
		case GLUT_KEY_HOME:
		{
			translated_key = KEY_HOME;
			break;
		}
		case GLUT_KEY_END:
		{
			translated_key = KEY_END;
			break;
		}
		case GLUT_KEY_INSERT:
		{
			translated_key = KEY_INSERT;
			break;
		}
	}
	return translated_key;
}

static int translate_mode()
{
	int mode = glutGetModifiers();

	bool new_key_state[3];

	new_key_state[0] = (mode & GLUT_ACTIVE_SHIFT) == GLUT_ACTIVE_SHIFT;
	new_key_state[1] = (mode & GLUT_ACTIVE_CTRL)  == GLUT_ACTIVE_CTRL;
	new_key_state[2] = (mode & GLUT_ACTIVE_ALT)   == GLUT_ACTIVE_ALT;

	if (new_key_state[0] && ! key_state[0] && type_func) type_func(KEY_SHIFT);
	if (!new_key_state[0] && key_state[0] && type_release_func) type_release_func(KEY_SHIFT);

	if (new_key_state[1] && ! key_state[1] && type_func) type_func(KEY_CONTROL);
	if (!new_key_state[1] && key_state[1] && type_release_func) type_release_func(KEY_CONTROL);

	if (new_key_state[2] && ! key_state[2] && type_func) type_func(KEY_ALT);
	if (!new_key_state[2] && key_state[2] && type_release_func) type_release_func(KEY_ALT);

	key_state[0] = new_key_state[0];
	key_state[1] = new_key_state[1];
	key_state[2] = new_key_state[2];
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

static void on_keydown(unsigned char key, int x, int y)
{
	translate_mode();
	if (type_func) type_func(key);
}

static void on_keyup(unsigned char key, int x, int y)
{
	translate_mode();
	if (type_release_func) type_release_func(key);
}

static void on_specialdown(int key, int x, int y)
{
	translate_mode();
	if (type_func) type_func(translate_key(key));
}

static void on_specialup(int key, int x, int y)
{
	translate_mode();
	if (type_release_func) type_release_func(translate_key(key));
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

