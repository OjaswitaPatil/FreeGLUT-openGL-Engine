#ifndef SHAPE_H
#define SHAPE_H

#include "globalHeaders.h"

typedef struct
{
	float x;
	float y;
	float z;
}Coordinates;

typedef enum
{
	TRIANGLE = 0,
	RECTANGLE,
	LINE
}ShapeType;


typedef struct
{
	ShapeType shapetype;
	Coordinates position;
	Coordinates scale;
	Coordinates rotationAngle;
	float color[3];
}Shape;

//function declarations
void drawShape(Shape *shape);
void drawTriangle(Shape *shape);
void drawRectangle(Shape *shape);




#endif

