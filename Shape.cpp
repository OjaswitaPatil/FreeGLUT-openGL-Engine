#include "Shape.h"

struct ScreenRotation screenRotation;

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

		case SPHERE:
		    drawSphere(shape);
			 break;	

	    case CYLINDER:
		    drawCylinder(shape);
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
	glLineWidth(1.0f);
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

void drawGridForEntireScene(void)
{
	glPushMatrix();

	//X-Axis
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);
	glEnd();

	for(int i = 0; i <= 20; i++)
	{
		glLineWidth(1.0f);
		glBegin(GL_LINES);
		glColor3f(0.5f, 0.5f, 0.5f);

		//lines on z axis
		glVertex3f(-10.0f, 0.0f, (float)i/2);
		glVertex3f(10.0f, 0.0f, (float)i/2);

		glVertex3f(-10.0f, 0.0f, -(float)i/2);
		glVertex3f(10.0f, 0.0f, -(float)i/2);

		//lines on X axis
		glVertex3f((float)i/2, 0.0f, -10.0f);
		glVertex3f((float)i/2, 0.0f, 10.0f);

		glVertex3f(-(float)i/2, 0.0f, -10.0f);
		glVertex3f(-(float)i/2, 0.0f, 10.0f);


		glEnd();
	}


	//Y Axis
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);
	glVertex3f(0.0f, -10.0f, 0.0f);
	glEnd();

	//z axis
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 20.0f);
	glVertex3f(0.0f, 0.0f, -20.0f);
	glEnd();

	glPopMatrix();
}

void drawSphere(Shape *shape)
{
	glPushMatrix();

	glTranslatef(shape->position.x, shape->position.y, shape->position.z);
	glRotatef(shape->rotationAngle.x, 1.0f, 0.0f, 0.0f);
	glRotatef(shape->rotationAngle.y, 0.0f, 1.0f, 0.0f);
	glRotatef(shape->rotationAngle.z, 0.0f, 0.0f, 1.0f);
	glScalef(shape->scale.x, shape->scale.y, shape->scale.z);

    GLUquadric* quadric = gluNewQuadric();  // Create a new quadric object

    // Set the drawing style for the sphere
	if((int)shape->customShapeAttributes[0] == 1)
    	gluQuadricDrawStyle(quadric, GLU_FILL);  // Fill the sphere
	else
		gluQuadricDrawStyle(quadric, GLU_LINE); 

    gluQuadricNormals(quadric, GLU_SMOOTH);  // Use smooth shading for normals

    // Draw the sphere
    glColor3f(shape->color[0], shape->color[1], shape->color[2]);
    gluSphere(quadric, 1.5f, (int)shape->customShapeAttributes[1], (int)shape->customShapeAttributes[2]);  // Radius = 1.0, slices = 32, stacks = 32

    gluDeleteQuadric(quadric);  // Clean up and delete the quadric object

	glPopMatrix();
}

void drawCylinder(Shape *shape) 
{
	glPushMatrix();

	glTranslatef(shape->position.x, shape->position.y, shape->position.z);
	glRotatef(shape->rotationAngle.x, 1.0f, 0.0f, 0.0f);
	glRotatef(shape->rotationAngle.y, 0.0f, 1.0f, 0.0f);
	glRotatef(shape->rotationAngle.z, 0.0f, 0.0f, 1.0f);
	glScalef(shape->scale.x, shape->scale.y, shape->scale.z);

    GLUquadric* quadric = gluNewQuadric();

    // Set the cylinder properties
    // Set the drawing style for the cylinder
	if((int)shape->customShapeAttributes[0] == 1)
    	gluQuadricDrawStyle(quadric, GLU_FILL); 
	else
		gluQuadricDrawStyle(quadric, GLU_LINE); 

    gluQuadricNormals(quadric, GLU_SMOOTH); // Smooth shading

    // Draw a cylinder with radius 1, height 3, and 32 slices
    glColor3f(shape->color[0], shape->color[1], shape->color[2]);
    gluCylinder(quadric, shape->customShapeAttributes[1] ,shape->customShapeAttributes[2], shape->customShapeAttributes[3],  (int)shape->customShapeAttributes[4], (int)shape->customShapeAttributes[5]);

    gluDeleteQuadric(quadric);  // Clean up

	glPopMatrix();
}


