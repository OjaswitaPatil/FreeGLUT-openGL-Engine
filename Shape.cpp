#include "Shape.h"

void drawShape(Shape *shape)
{
	void drawTriangle(Shape *shape);
	void drawRectangle(Shape *shape);

	switch(shape->shapetype)
	{
		case TRIANGLE:
             drawTriangle(shape);
			 break;

	    case RECTANGLE:
		     drawRectangle(shape);
			 break;	 
	}
}

void drawTriangle(Shape *shape)
{
	glPushMatrix();

	glTranslatef(shape->position.x, shape->position.y, shape->position.z);
	glRotatef(shape->rotationAngle.x, 1.0f, 0.0f, 0.0f);
	glRotatef(shape->rotationAngle.y, 0.0f, 1.0f, 0.0f);
	glRotatef(shape->rotationAngle.z, 0.0f, 0.0f, 1.0f);
	glScalef(shape->scale.x, shape->scale.y, shape->scale.z);

	glBegin(GL_TRIANGLES);
	glColor3f(shape->color[0], shape->color[1], shape->color[2]);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);

	glEnd();

	glPopMatrix();
}

void drawRectangle(Shape *shape)
{
	glPushMatrix();

	glTranslatef(shape->position.x, shape->position.y, shape->position.z);
	glRotatef(shape->rotationAngle.x, 1.0f, 0.0f, 0.0f);
	glRotatef(shape->rotationAngle.y, 0.0f, 1.0f, 0.0f);
	glRotatef(shape->rotationAngle.z, 0.0f, 0.0f, 1.0f);
	glScalef(shape->scale.x, shape->scale.y, shape->scale.z);


	glBegin(GL_QUADS);

	glColor3f(shape->color[0], shape->color[1], shape->color[2]);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);

	glEnd();

	glPopMatrix();
}
