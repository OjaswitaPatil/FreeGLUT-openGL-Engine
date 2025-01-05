// header files
#include "globalHeaders.h"
#include "shape.h"
#include "imGuiExtenstion.h"
#include "LinkedList.h"
#include "SaveAndLoadCSV.h"

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
	void keyboard_up_callback(unsigned char, int, int);
	void special_key_callback(int, int, int);
	void special_key_up_callback(int, int, int);
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
    glutKeyboardUpFunc(keyboard_up_callback);
    glutSpecialFunc(special_key_callback);
    glutSpecialUpFunc(special_key_up_callback);
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
	// Start the ImGui frame
	startimGuiFrame();
    renderimGUIControls();

    //------------------------DRAW--------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Load the identity matrix to reset transformations
    glLoadIdentity();

    
		glPushMatrix();

			glTranslatef(0.0f, 0.0f, -10.0f);
			glRotatef(screenRotation.rotate.x, 1.0f, 0.0f, 0.0f);
			glRotatef(screenRotation.rotate.y, 0.0f, 1.0f, 0.0f);
			glRotatef(screenRotation.rotate.z, 0.0f, 0.0f, 1.0f);

            if(showGrid == true)
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
	//imgui-----------------------------
	// Get the ImGui IO structure
	ImGuiIO& io = ImGui::GetIO();

    // If the key is within bounds, update the corresponding key state in ImGui
    if (key < 256) {
        io.KeysDown[key] = true;
    }

	// Add the character to ImGui input buffer
    io.AddInputCharacter(key);

	//--------------------------------

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
// GLUT keyboard up callback
void keyboard_up_callback(unsigned char key, int x, int y)
{
    ImGuiIO& io = ImGui::GetIO();

    // Reset the key state when the key is released
    if (key < 256) {
        io.KeysDown[key] = false;
    }
}

// GLUT special key callback (for arrow keys, etc.)
void special_key_callback(int key, int x, int y)
{
    ImGuiIO& io = ImGui::GetIO();

    // Translate special keys (like arrow keys) to ImGui key codes
    if (key == GLUT_KEY_LEFT) io.KeysDown[ImGuiKey_LeftArrow] = true;
    if (key == GLUT_KEY_RIGHT) io.KeysDown[ImGuiKey_RightArrow] = true;
    if (key == GLUT_KEY_UP) io.KeysDown[ImGuiKey_UpArrow] = true;
    if (key == GLUT_KEY_DOWN) io.KeysDown[ImGuiKey_DownArrow] = true;
}

// GLUT special key up callback
void special_key_up_callback(int key, int x, int y)
{
    ImGuiIO& io = ImGui::GetIO();

    // Reset special key states when they are released
    if (key == GLUT_KEY_LEFT) io.KeysDown[ImGuiKey_LeftArrow] = false;
    if (key == GLUT_KEY_RIGHT) io.KeysDown[ImGuiKey_RightArrow] = false;
    if (key == GLUT_KEY_UP) io.KeysDown[ImGuiKey_UpArrow] = false;
    if (key == GLUT_KEY_DOWN) io.KeysDown[ImGuiKey_DownArrow] = false;
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
