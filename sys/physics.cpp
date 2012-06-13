#include <map>

#include <ode/ode.h>

#include <iostream>

#include "physics.h"

#define MAX_CONTACTS 10

typedef struct
{
	dWorldID world;
	dSpaceID space;
	dJointGroupID contact_group;
} World;

typedef struct
{
	dBodyID body;
	dMass   mass;
	dGeomID geom;
	void*   data;
} Object3D;

typedef struct
{
	dTriIndex indexes[6];
	dVector3  vertices[4];
} PlaneTriMesh;

static std::map<int, World> worlds;
static int world_last_id = 0;

static std::map<int, Object3D> objects;
static int object_last_id = 0;

static void on_collide(void *data, dGeomID o1, dGeomID o2);


void physics_init()
{
	dInitODE();
}

void physics_close()
{
	dCloseODE();
}


int physics_create_world(double gravity)
{
	World world;
	world.world = dWorldCreate();
	world.space = dSimpleSpaceCreate(0);
	world.contact_group = dJointGroupCreate(0);
	dWorldSetGravity(world.world, 0.0, gravity, 0.0);

	worlds.insert(std::make_pair(world_last_id, world));
	return world_last_id++;
}

void physics_destroy_world(int world_id)
{
	World world = worlds.at(world_id);

	dJointGroupDestroy(world.contact_group);
	dSpaceDestroy(world.space);
	dWorldDestroy(world.world);

	worlds.erase(world_id);
}


int physics_create_fixed_plane(int world_id, double pos_x, double pos_y, double pos_z, double width, double height)
{
	World world = worlds.at(world_id);
	Object3D object;
	//PlaneTriMesh plane_mesh = {
	object.data = new PlaneTriMesh({
		{2, 1, 0, 3, 2, 0}, // indexes
		{
			{ (width / 2), 0.0,  (height / 2)},
			{-(width / 2), 0.0,  (height / 2)},
			{-(width / 2), 0.0, -(height / 2)},
			{ (width / 2), 0.0, -(height / 2)}
		} // vertices
	});

	/*dTriIndex indexes[6] = {2, 1, 0, 3, 2, 0};
	dVector3 vertices[4] = {
		{ (width / 2), 0.0,  (height / 2)},
		{-(width / 2), 0.0,  (height / 2)},
		{-(width / 2), 0.0, -(height / 2)},
		{ (width / 2), 0.0, -(height / 2)}
	};
	plane_mesh.indexes = indexes;
	plane_mesh.vertices = vertices;*/
	//object.data = &plane_mesh;
	PlaneTriMesh &plane_mesh = *(PlaneTriMesh*)object.data;

	dTriMeshDataID tri_mesh = dGeomTriMeshDataCreate();
	dGeomTriMeshDataBuildSimple(tri_mesh, (dReal*)plane_mesh.vertices, 4, plane_mesh.indexes, 6);
	object.geom = dCreateTriMesh(world.space, tri_mesh, NULL, NULL, NULL);

	dGeomSetData(object.geom, (void*)"Plane");
	dGeomSetPosition(object.geom, 0, -10.0, 0);

	dMassSetZero(&object.mass);
	object.body = NULL;
	
	objects.insert(std::make_pair(object_last_id, object));

	std::cout << "object " << object_last_id << " => " << std::hex << object.geom << std::endl;


	dVector3 v1, v2, v3;
	std::cout << "xxxxx" << std::endl;
	dGeomTriMeshGetTriangle(object.geom, 0, &v1, &v2, &v3);
	std::cout << "(" << v1[0] << "x" << v1[1] << "x" << v1[2] << ")" << std::endl;
	std::cout << "(" << v2[0] << "x" << v2[1] << "x" << v2[2] << ")" << std::endl;
	std::cout << "(" << v3[0] << "x" << v3[1] << "x" << v3[2] << ")" << std::endl;
	dGeomTriMeshGetTriangle(object.geom, 1, &v1, &v2, &v3);
	std::cout << "(" << v1[0] << "x" << v1[1] << "x" << v1[2] << ")" << std::endl;
	std::cout << "(" << v2[0] << "x" << v2[1] << "x" << v2[2] << ")" << std::endl;
	std::cout << "(" << v3[0] << "x" << v3[1] << "x" << v3[2] << ")" << std::endl;


	return object_last_id++;
}

void physics_destroy_object(int object_id)
{
	Object3D object = objects.at(object_id);
	if (object.body) dBodyDestroy(object.body);
	if (object.geom) dGeomDestroy(object.geom);
	objects.erase(object_id);
}


void physics_update(double time)
{
	for (std::map<int, World>::iterator it = worlds.begin(); it != worlds.end(); it++)
	{
		dJointGroupEmpty(it->second.contact_group);
		dSpaceCollide(it->second.space, &it->second, on_collide);
		dWorldQuickStep(it->second.world, time);
	}
}


Vertex physics_get_position(int object_id)
{
	Object3D object = objects.at(object_id);

	const dReal *realP = dGeomGetPosition(object.geom);
	Vertex position;
	position.x = realP[0];
	position.y = realP[1];
	position.z = realP[2];
	return position;
}

int physics_get_triangles(int object_id, Vertex *vertices, int triangles)
{
	Object3D object = objects.at(object_id);

	if (dGeomGetClass(object.geom) != dTriMeshClass) return -1;

	int count = dGeomTriMeshGetTriangleCount(object.geom);

	if (!vertices) return count;

	if (count > triangles) count = triangles;

	std::cout << "object " << object_id << " => " << std::hex << object.geom << std::endl;

	dGeomGetPosition(object.geom);

	dVector3 v1, v2, v3;
	std::cout << "=====" << std::endl;
	dGeomTriMeshGetTriangle(object.geom, 0, &v1, &v2, &v3);
	std::cout << "(" << v1[0] << "x" << v1[1] << "x" << v1[2] << ")" << std::endl;
	std::cout << "(" << v2[0] << "x" << v2[1] << "x" << v2[2] << ")" << std::endl;
	std::cout << "(" << v3[0] << "x" << v3[1] << "x" << v3[2] << ")" << std::endl;
	dGeomTriMeshGetTriangle(object.geom, 1, &v1, &v2, &v3);
	std::cout << "(" << v1[0] << "x" << v1[1] << "x" << v1[2] << ")" << std::endl;
	std::cout << "(" << v2[0] << "x" << v2[1] << "x" << v2[2] << ")" << std::endl;
	std::cout << "(" << v3[0] << "x" << v3[1] << "x" << v3[2] << ")" << std::endl;


	for (int i = 0; i < count; i++)
	{
		dVector3 vector[3];
		std::cout << "(" << i << ")" << std::endl;
		dGeomTriMeshGetTriangle(object.geom, i, &vector[0], &vector[1], &vector[2]);
		std::cout << "(OK)" << std::endl;
		for (int j = 0; j < 3; j++)
		{
			vertices[i * 3 + j].x = vector[j][0];
			vertices[i * 3 + j].y = vector[j][1];
			vertices[i * 3 + j].z = vector[j][2];
			std::cout << "(" << vertices[i * 3 + j].x << "x" << vertices[i * 3 + j].y << "x" << vertices[i * 3 + j].z << ")" << std::endl;
		}
	}
	return count;
}


static void on_collide(void *data, dGeomID o1, dGeomID o2)
{
	World &world = *(World*)data;

	dBodyID body1 = dGeomGetBody(o1);
	dBodyID body2 = dGeomGetBody(o2);
 
	dContact contact[MAX_CONTACTS];
 
	for (int i = 0; i < MAX_CONTACTS; i++) {
		contact[i].surface.mode = dContactBounce;
		contact[i].surface.bounce = 0.5;
		contact[i].surface.mu = 100.0;
	}
 
	int collisions = dCollide(o1, o2, MAX_CONTACTS, &contact[0].geom, sizeof(dContact));
	if (collisions) {
		for (int i = 0; i < collisions; ++i) {
			dJointID c = dJointCreateContact(world.world, world.contact_group, &contact[i]);
			dJointAttach(c, body1, body2);
		}
	}
}

