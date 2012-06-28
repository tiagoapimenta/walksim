#include <map>

#include <ode/ode.h>

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

/*typedef struct
{
	dJointID joint;
} Joint;*/

static std::map<int, World> worlds;
static int world_last_id = 0;

static std::map<int, Object3D> objects;
static int object_last_id = 0;

static std::map<int, dJointID> joints;
static int joint_last_id = 0;
static void(*collider_func)(int objectA, int objectB) = NULL;

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

	PlaneTriMesh &plane_mesh = *(PlaneTriMesh*)malloc(sizeof(PlaneTriMesh));
	plane_mesh.indexes[4] = plane_mesh.indexes[0] = 2;
	plane_mesh.indexes[1] = 1;
	plane_mesh.indexes[5] = plane_mesh.indexes[2] = 0;
	plane_mesh.indexes[3] = 3;
	plane_mesh.vertices[0][1] = plane_mesh.vertices[1][1] = plane_mesh.vertices[2][1] = plane_mesh.vertices[3][1] = 0.0;
	plane_mesh.vertices[0][0] = plane_mesh.vertices[3][0] = width / 2;
	plane_mesh.vertices[1][0] = plane_mesh.vertices[2][0] = -(width / 2);
	plane_mesh.vertices[0][2] = plane_mesh.vertices[1][2] = height / 2;
	plane_mesh.vertices[2][2] = plane_mesh.vertices[3][2] = -(height / 2);
	object.data = &plane_mesh;

	dTriMeshDataID tri_mesh = dGeomTriMeshDataCreate();
	dGeomTriMeshDataBuildSimple(tri_mesh, (dReal*)plane_mesh.vertices, 4, plane_mesh.indexes, 6);
	object.geom = dCreateTriMesh(world.space, tri_mesh, NULL, NULL, NULL);

	//dGeomSetData(object.geom, (void*)object_last_id);
	dGeomSetPosition(object.geom, 0, -10.0, 0);

	dMassSetZero(&object.mass);
	object.body = NULL;
	
	objects.insert(std::make_pair(object_last_id, object));
	return object_last_id++;
}

int physics_create_box(int world_id, double pos_x, double pos_y, double pos_z, double width, double height, double length, double mass)
{
	World world = worlds.at(world_id);
	Object3D object;

	object.body = dBodyCreate(world.world);
	object.geom = dCreateBox(world.space, width, height, length);
	object.data = NULL;

	dBodySetPosition(object.body, pos_x, pos_y, pos_z);

	dMassSetBox(&object.mass, 1.0, width, height, length);
	dMassAdjust(&object.mass, mass);

	dBodySetMass(object.body, &object.mass);
	dGeomSetBody(object.geom, object.body);
	//dGeomSetData(object.geom, (void*)object_last_id);

	objects.insert(std::make_pair(object_last_id, object));
	return object_last_id++;
}

void physics_destroy_object(int object_id)
{
	Object3D object = objects.at(object_id);
	if (object.body) dBodyDestroy(object.body);
	if (object.geom) dGeomDestroy(object.geom);
	if (object.data) free(object.data);
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

	//const dReal *realP = dGeomGetPosition(object.geom);
	const dReal *realP = dBodyGetPosition(object.body);

	Vertex position;
	position.x = realP[0];
	position.y = realP[1];
	position.z = realP[2];
	return position;
}

Vertex physics_get_lengths(int object_id)
{
	Object3D object = objects.at(object_id);

	dVector3 sides;
	dGeomBoxGetLengths(object.geom, sides);

	Vertex lengths;
	lengths.x = sides[0];
	lengths.y = sides[1];
	lengths.z = sides[2];
	return lengths;
}

Transform physics_get_rotation(int object_id)
{
	Object3D object = objects.at(object_id);

	const dReal *realP = dBodyGetRotation(object.body);

	Transform rotation = {};
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			rotation.matrix[i][j] = realP[i * 4 + j];
		}
	}
	return rotation;
}


int physics_get_triangles(int object_id, Vertex *vertices, int triangles)
{
	Object3D object = objects.at(object_id);

	if (dGeomGetClass(object.geom) != dTriMeshClass) return -1;

	int count = dGeomTriMeshGetTriangleCount(object.geom);

	if (!vertices) return count;

	if (count > triangles) count = triangles;

	for (int i = 0; i < count; i++)
	{
		dVector3 vector[3];
		dGeomTriMeshGetTriangle(object.geom, i, &vector[0], &vector[1], &vector[2]);
		for (int j = 0; j < 3; j++)
		{
			vertices[i * 3 + j].x = vector[j][0];
			vertices[i * 3 + j].y = vector[j][1];
			vertices[i * 3 + j].z = vector[j][2];
		}
	}
	return count;
}


int physics_create_hinge_joint(int world_id, int object_id1, int object_id2, double x, double y, double z, double axisX, double axisY, double axisZ)
{
	World world = worlds.at(world_id);
	Object3D object1 = objects.at(object_id1);
	Object3D object2 = objects.at(object_id2);

	dJointID joint = dJointCreateHinge(world.world, NULL); //world.contact_group
	dJointAttach(joint, object1.body, object2.body);
	dJointSetHingeAnchor(joint, x, y, z);
	dJointSetHingeAxis(joint, axisX, axisY, axisZ);

	joints.insert(std::make_pair(joint_last_id, joint));
	return joint_last_id++;
}

void physics_destroy_joint(int joint_id)
{
	dJointID joint = joints.at(joint_id);
	dJointDestroy(joint);
	joints.erase(joint_id);
}

Vertex physics_get_hinge_anchor(int joint_id)
{
	dJointID joint = joints.at(joint_id);

	dVector3 anchor;
	dJointGetHingeAnchor(joint, anchor);

	Vertex position;
	position.x = anchor[0];
	position.y = anchor[1];
	position.z = anchor[2];
	return position;
}

double physics_get_hinge_angle(int joint_id)
{
	dJointID joint = joints.at(joint_id);
	return dJointGetHingeAngle(joint);
}

double physics_get_hinge_angle_rate(int joint_id)
{
	dJointID joint = joints.at(joint_id);
	return dJointGetHingeAngleRate(joint);
}

void physics_add_hinge_torque(int joint_id, double torque)
{
	dJointID joint = joints.at(joint_id);
	dJointAddHingeTorque(joint, torque);
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

		if (collider_func)
		{
			int objectA = -1, //(int)dGeomGetData(o1),
				objectB = -1; //(int)dGeomGetData(o2);
			
			for (std::map<int, Object3D>::iterator it = objects.begin(); it != objects.end(); it++)
			{
				if (it->second.geom == o1)
				{
					objectA = it->first;
					if (objectB != -1) break;
				}
				if (it->second.geom == o2)
				{
					objectB = it->first;
					if (objectA != -1) break;
				}
			}

			collider_func(objectA, objectB);
		}
	}
}


void physics_set_collider(void(*collider)(int objectA, int objectB))
{
	collider_func = collider;
}

