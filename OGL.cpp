// header files
#include "globalHeaders.h"
#include "shape.h"
#include "imGuiExtenstion.h"
#include "LinkedList.h"

// global variable declarations
BOOL bFullScreen = FALSE;
int windowWidth = 1280;
int windowHeight = 720;


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
	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();
	// gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
	// glMatrixMode(GL_MODELVIEW);

    //update imGui Display Size as per window size
	updateimGuiDisplaySize(width, height);
}

void display(void)
{
	//----------------------IMGUI----------------------------
	{
		// Start the ImGui frame
		startimGuiFrame();

		ImGui::Begin("Engine's Controls");

		if (ImGui::Button("Create Triangle"))  
		{                        
			createShape(TRIANGLE);
		}

		if (ImGui::Button("Create Rectangle")) 
		{                   
			createShape(RECTANGLE);
		}

		if(selectedShape != NULL) //means linklist has at least one node
		{	

			//--- TRANSLATE------
			ImGui::SliderFloat("PositionX", &(selectedShape->shape.position.x), -1.0f, 1.0f);
			ImGui::SliderFloat("PositionY", &(selectedShape->shape.position.y), -1.0f, 1.0f);

			//--- SCALE------
			float beforeScaleAllX = selectedShape->shape.scale.x;
			ImGui::SliderFloat("ScaleAll", &(selectedShape->shape.scale.x), 0.0f, 1.0f);
			if(beforeScaleAllX !=  selectedShape->shape.scale.x )
			{
				selectedShape->shape.scale.y = selectedShape->shape.scale.x;
				selectedShape->shape.scale.z = selectedShape->shape.scale.x;
			}

			ImGui::SliderFloat("ScaleX", &(selectedShape->shape.scale.x), 0.0f, 1.0f);
			ImGui::SliderFloat("ScaleY", &(selectedShape->shape.scale.y), 0.0f, 1.0f);

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
	glClear(GL_COLOR_BUFFER_BIT);

	//Draw all shapes
	drawAllShapes();

 	// Render ImGui
    renderimGui();
	//--------------------------------------------------------

    glutPostRedisplay();
	glutSwapBuffers();
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
