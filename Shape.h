#ifndef SHAPE_H
#define SHAPE_H

#include "globalHeaders.h"

#define MAX_COUNT_OF_COLORS 6
#define MAX_COUNT_OF_CUSTOMSHAPEATTRIBUTES 10
#define COLORRGBA 4

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
	CUBE,
	SPHERE,
	CYLINDER
}ShapeType;

typedef struct
{
	ShapeType shapetype;
	Coordinates position;
	Coordinates scale;
	Coordinates rotationAngle;
	int colorsCount;
	float *colors;
	int customShapeAttributesCount;
	float *customShapeAttributes;
}Shape;

struct ScreenRotation
{
	Coordinates rotate;
};
extern struct ScreenRotation screenRotation;

//function declarations
void drawShape(Shape *shape);
void drawTriangle(Shape *shape);
void drawRectangle(Shape *shape);
void drawCube(Shape *shape);
void drawGridAroundSelectedShape(Shape *shape);
void drawGridForEntireScene(void);
void drawSphere(Shape *shape);
void drawCylinder(Shape *shape) ;

ShapeType getShapeType(int shapeType);


#endif

