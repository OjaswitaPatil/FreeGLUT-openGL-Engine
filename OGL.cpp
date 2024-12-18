// header files
#include "globalHeaders.h"
#include "shape.h"
#include "imGuiExtenstion.h"
#include "LinkedList.h"

// global variable declarations
BOOL bFullScreen = FALSE;
int windowWidth = 1280;
int windowHeight = 720;

struct ScreenRotation
{
	Coordinates rotate;
};

struct ScreenRotation screenRotation;

// Entry-point function
int main(int argc, char* argv[])
{
	// local function declarations
	int initialize(void);
	void resize(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void mouseMotion(int x, int y);
	void uninitialize(void);
	void MainLoopStep();
	void imGuiInitialization(void);

	// code
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Ojaswita Vinay Patil");

	initialize();

	//imGui initialization
	imGuiInitialization();

    glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion); // For motion with a pressed mouse button
    glutPassiveMotionFunc(mouseMotion); // Register passive mouse motion
	glutCloseFunc(uninitialize);

	glutMainLoop();

	return(0);
}

int initialize(void)
{
	// code
	glClearColor(
		0.0f,									//red
		0.0f,									//green
		0.0f,									//blue
		1.0f 									//alpha
	);

	// Enable depth testing
    glEnable(GL_DEPTH_TEST);


	//initialize scene rotation-----------
	screenRotation.rotate.x = 9.0f;
	screenRotation.rotate.y = 12.0f;
	screenRotation.rotate.z = 0.0f;
	//-------------------------------

	return(0);
}

void resize(int width, int height)
{
	void updateimGuiDisplaySize(int width, int height);
	// code

	// Update the window size
	windowWidth = width;
	windowHeight = height;

	glViewport(0, 0, width, height);
	
	// Set up the projection matrix for 3D viewing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 200.0); // FOV, aspect ratio, near and far planes
    glMatrixMode(GL_MODELVIEW); // Switch back to modelview matrix

    //update imGui Display Size as per window size
	updateimGuiDisplaySize(width, height);
}

void display(void)
{
	//----------------------IMGUI----------------------------
	//engine controls
	{
		// Start the ImGui frame
		startimGuiFrame();

		ImGui::Begin("Engine's Controls");

		//scene rotoation
		ImGui::SliderFloat("SceneRotoationX", &(screenRotation.rotate.x),-360.0f, 360.0f);
		ImGui::SliderFloat("SceneRotoationY", &(screenRotation.rotate.y),-360.0f, 360.0f);
		ImGui::SliderFloat("SceneRotoationZ", &(screenRotation.rotate.z),-360.0f, 360.0f);
		if (ImGui::Button("Reset Scene Rotation"))  
		{                        
			screenRotation.rotate.x = 9.0f;
			screenRotation.rotate.y = 12.0f;
			screenRotation.rotate.z = 0.0f;
		}


		if (ImGui::Button("Create Triangle"))  
		{                        
			createShape(TRIANGLE);
		}

		if (ImGui::Button("Create Rectangle")) 
		{                   
			createShape(RECTANGLE);
		}

		if (ImGui::Button("Create cube")) 
		{                   
			createShape(CUBE);
		}

		if(selectedShape != NULL) //means linklist has at least one node
		{	

			//--- TRANSLATE------
			ImGui::SliderFloat("PositionX", &(selectedShape->shape.position.x), -15.0f, 15.0f);
			ImGui::SliderFloat("PositionY", &(selectedShape->shape.position.y), -15.0f, 15.0f);
			ImGui::SliderFloat("PositionZ", &(selectedShape->shape.position.z), -15.0f, 15.0f);

			//--- SCALE------
			float beforeScaleAllX = selectedShape->shape.scale.x;
			ImGui::SliderFloat("ScaleAll", &(selectedShape->shape.scale.x), 0.0f, 3.0f);
			if(beforeScaleAllX !=  selectedShape->shape.scale.x )
			{
				selectedShape->shape.scale.y = selectedShape->shape.scale.x;
				selectedShape->shape.scale.z = selectedShape->shape.scale.x;
			}

			ImGui::SliderFloat("ScaleX", &(selectedShape->shape.scale.x), -1.0f, 5.0f);
			ImGui::SliderFloat("ScaleY", &(selectedShape->shape.scale.y), -1.0f, 5.0f);
			ImGui::SliderFloat("ScaleZ", &(selectedShape->shape.scale.z), -1.0f, 5.0f);

			//--- Rotation------
			ImGui::SliderFloat("rotationX", &(selectedShape->shape.rotationAngle.x), 0.0f, 360.0f);
			ImGui::SliderFloat("rotationY", &(selectedShape->shape.rotationAngle.y), 0.0f, 360.0f);
			ImGui::SliderFloat("rotationZ", &(selectedShape->shape.rotationAngle.z), 0.0f, 360.0f);

			if (ImGui::Button("Next Shape"))  
			{
				selectedShape = selectedShape->next;
			}
			if (ImGui::Button("previous Shape"))  
			{    
				selectedShape = selectedShape->pre;
			}
			
			ImGui::Text("currently selected shape= %d", selectedShape->shape.shapetype);

			//ImGui::SameLine();

			ImGui::ColorEdit3("color", (float*)selectedShape->shape.color);


			if (ImGui::Button("Delete Shape"))  
			{    
				deleteShape(selectedShape);
			}
		}

		ImGui::End();
	}
	//--------------------------------------------------------

    //------------------------DRAW--------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Load the identity matrix to reset transformations
    glLoadIdentity();





	glPushMatrix();

		glTranslatef(0.0f, 0.0f, -5.0f);
		glRotatef(screenRotation.rotate.x, 1.0f, 0.0f, 0.0f);
		glRotatef(screenRotation.rotate.y, 0.0f, 1.0f, 0.0f);
		glRotatef(screenRotation.rotate.z, 0.0f, 0.0f, 1.0f);

		drawGridForEntireScene();

		//Draw all shapes
		drawAllShapes();

	glPopMatrix();

 	// Render ImGui
    renderimGui();
	//--------------------------------------------------------

	glutSwapBuffers();
    glutPostRedisplay();

}

void keyboard(unsigned char key, int x, int y)
{
	// code
	switch (key)
	{
	case 27:
		glutLeaveMainLoop();
		break;
	case 'F':
	case 'f':
		if (bFullScreen == FALSE)
		{
			glutFullScreen();
			bFullScreen = TRUE;
		}
		else
		{
			glutLeaveFullScreen();
			bFullScreen = FALSE;
		}
		break;
	default:
		break;
    }
}

void mouse(int button, int state, int x, int y)
{
	void setupMouseClickInimGui(int button, int state, int x, int y);

	// code
	//setup MouseClick In imGui
	setupMouseClickInimGui(button, state, x, y);

	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		//glutLeaveMainLoop();
		break;
	default:
		break;
	}
}

void mouseMotion(int x, int y)
{
    void setupMouseMotionInimGui(int x, int y);
    
	//setup MouseMotion In imGui
	setupMouseMotionInimGui(x, y);

}

void uninitialize(void)
{
	void imGuiUninitialization(void);
	// code
	
	//imGui Uninitialization
	imGuiUninitialization();
}
