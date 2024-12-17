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

	    case CUBE:
		    drawCube(shape);
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

void drawCube(Shape *shape)
{
	glPushMatrix();

	    glTranslatef(shape->position.x, shape->position.y, shape->position.z);
		glRotatef(shape->rotationAngle.x, 1.0f, 0.0f, 0.0f);
		glRotatef(shape->rotationAngle.y, 0.0f, 1.0f, 0.0f);
		glRotatef(shape->rotationAngle.z, 0.0f, 0.0f, 1.0f);
		glScalef(shape->scale.x, shape->scale.y, shape->scale.z);

		// Draw the cube with separate colors for each face
        glBegin(GL_QUADS);  // Draw each face of the cube as a quadrilateral

        // Front face (Red)
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom-left
        glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom-right
        glVertex3f( 1.0f,  1.0f,  1.0f);  // Top-right
        glVertex3f(-1.0f,  1.0f,  1.0f);  // Top-left

        // Back face (Green)
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom-left
        glVertex3f(-1.0f,  1.0f, -1.0f);  // Top-left
        glVertex3f( 1.0f,  1.0f, -1.0f);  // Top-right
        glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom-right

        // Top face (Blue)
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f);  // Back-left
        glVertex3f(-1.0f,  1.0f,  1.0f);  // Front-left
        glVertex3f( 1.0f,  1.0f,  1.0f);  // Front-right
        glVertex3f( 1.0f,  1.0f, -1.0f);  // Back-right

        // Bottom face (Yellow)
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);  // Back-left
        glVertex3f( 1.0f, -1.0f, -1.0f);  // Back-right
        glVertex3f( 1.0f, -1.0f,  1.0f);  // Front-right
        glVertex3f(-1.0f, -1.0f,  1.0f);  // Front-left

        // Right face (Cyan)
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom-front
        glVertex3f( 1.0f,  1.0f, -1.0f);  // Top-front
        glVertex3f( 1.0f,  1.0f,  1.0f);  // Top-back
        glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom-back

        // Left face (Magenta)
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom-back
        glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom-front
        glVertex3f(-1.0f,  1.0f,  1.0f);  // Top-front
        glVertex3f(-1.0f,  1.0f, -1.0f);  // Top-back

        glEnd();  // End drawing the cube face

	glPopMatrix();
}


void drawGridAroundSelectedShape(Shape *shape)
{
	glPushMatrix();

	glTranslatef(shape->position.x, shape->position.y, shape->position.z);
	glRotatef(shape->rotationAngle.x, 1.0f, 0.0f, 0.0f);
	glRotatef(shape->rotationAngle.y, 0.0f, 1.0f, 0.0f);
	glRotatef(shape->rotationAngle.z, 0.0f, 0.0f, 1.0f);
	glScalef(shape->scale.x, shape->scale.y, shape->scale.z);

	//X-Axis
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-3.0f, 0.0f, 0.0f);
	glVertex3f(3.0f, 0.0f, 0.0f);
	glEnd();

	//Y Axis
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 3.0f, 0.0f);
	glVertex3f(0.0f, -3.0f, 0.0f);
	glEnd();

	//z axis
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 3.0f);
	glVertex3f(0.0f, 0.0f, -3.0f);
	glEnd();

	glPopMatrix();
}

