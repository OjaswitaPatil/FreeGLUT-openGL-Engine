// header files
#include "globalHeaders.h"
#include "shape.h"
#include "imGuiExtenstion.h"

// global variable declarations
BOOL bFullScreen = FALSE;
int windowWidth = 1280;
int windowHeight = 720;

Shape shape[2];

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



	for(int i = 0; i < 2; i++)
	{


		shape[i].position.x = 0.0f;
		shape[i].position.y = 0.0f;
		shape[i].position.z = 0.0f;

		shape[i].rotationAngle.x = 0.0f;
		shape[i].rotationAngle.y = 0.0f;
		shape[i].rotationAngle.z = 0.0f;

		shape[i].scale.x = 0.15f;
		shape[i].scale.y = 0.15f;
		shape[i].scale.z = 0.15f;

		shape[i].color[0] = 1.0f;
		shape[i].color[1] = 0.0f;
		shape[i].color[2] = 0.0f;

	}

	shape[0].shapetype = TRIANGLE;
	shape[1].shapetype = RECTANGLE;



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
	void startimGuiFrame(void);
	void renderimGui(void);

	//----------------------IMGUI----------------------------
	{
		// Start the ImGui frame
		startimGuiFrame();

		ImGui::Begin("Engine's Controls");

		//--- TRANSLATE------
			ImGui::SliderFloat("PositionX", &(shape->position.x), -1.0f, 1.0f);
			ImGui::SliderFloat("PositionY", &(shape->position.y), -1.0f, 1.0f);

			//--- SCALE------
			float beforeScaleAllX = shape->scale.x;
			ImGui::SliderFloat("ScaleAll", &(shape->scale.x), 0.0f, 1.0f);
			if(beforeScaleAllX !=  shape->scale.x )
			{
				shape->scale.y = shape->scale.x;
				shape->scale.z = shape->scale.x;
			}

			ImGui::SliderFloat("ScaleX", &(shape->scale.x), 0.0f, 1.0f);
			ImGui::SliderFloat("ScaleY", &(shape->scale.y), 0.0f, 1.0f);

			//--- Rotation------
			ImGui::SliderFloat("rotationX", &(shape->rotationAngle.x), 0.0f, 360.0f);
			ImGui::SliderFloat("rotationY", &(shape->rotationAngle.y), 0.0f, 360.0f);
			ImGui::SliderFloat("rotationZ", &(shape->rotationAngle.z), 0.0f, 360.0f);

            ImGui::ColorEdit3("color", (float*)shape->color);
	
		ImGui::End();
	}
	//--------------------------------------------------------
	

	// code
	glClear(GL_COLOR_BUFFER_BIT);

	drawShape(&shape[0]);

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
