#include "imGuiExtenstion.h"


void imGuiInitialization(void)
{
	//Setup ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	ImGui::StyleColorsDark(); // Setup ImGui style

	// Key Mapping After ImGui Initialization
	io.KeyMap[ImGuiKey_Tab] = '\t';
	io.KeyMap[ImGuiKey_LeftArrow] = GLUT_KEY_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = GLUT_KEY_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = GLUT_KEY_UP;
	io.KeyMap[ImGuiKey_DownArrow] = GLUT_KEY_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = GLUT_KEY_PAGE_UP;
	io.KeyMap[ImGuiKey_PageDown] = GLUT_KEY_PAGE_DOWN;
	io.KeyMap[ImGuiKey_Home] = GLUT_KEY_HOME;
	io.KeyMap[ImGuiKey_End] = GLUT_KEY_END;
	io.KeyMap[ImGuiKey_Delete] = GLUT_KEY_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = '\b';
	io.KeyMap[ImGuiKey_Enter] = '\r';
	io.KeyMap[ImGuiKey_Escape] = 27; // ESC key
	io.KeyMap[ImGuiKey_Space] = ' '; // Space key

	// Setup Platform/Renderer backends
	ImGui_ImplGLUT_Init();
	ImGui_ImplOpenGL2_Init();
}

void updateimGuiDisplaySize(int width, int height)
{
    // Update ImGui display size
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2((float)width, (float)height);
}

void startimGuiFrame(void)
{
    // Start the Dear ImGui frame
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGLUT_NewFrame();
	ImGui::NewFrame();
}

void renderimGui(void)
{
    // Rendering
	ImGui::Render();
	// Render ImGui
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void setupMouseClickInimGui(int button, int state, int x, int y)
{
    ImGuiIO& io = ImGui::GetIO();
	if (button == GLUT_LEFT_BUTTON) {
		io.MouseDown[0] = (state == GLUT_DOWN); // Left mouse button
	}
	io.MousePos = ImVec2((float)x, (float)y); // Update mouse position
}

void setupMouseMotionInimGui(int x, int y)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2((float)x, (float)y);
}

void imGuiUninitialization(void)
{
    // Cleanup ImGui
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGLUT_Shutdown();
	ImGui::DestroyContext();
}

