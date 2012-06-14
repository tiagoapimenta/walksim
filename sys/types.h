#ifndef TYPES_H
#define TYPES_H

typedef struct
{
	double x;
	double y;
	double z;
} Vertex;

typedef union
{
	double matrix[4][4];
	struct {
		double x;
		double y;
		double z;
		double w;
	} vertices[4];
} Transform;

#endif

