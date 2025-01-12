#include "imGuiExtenstion.h"

bool showGrid = true;
char input_text[MAX_TEXT_INPUT_SIZE];

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

void renderimGUIControls(void)
{
	//engine controls
	static float scaleAllOffSet = 0.0f;
	if(ImGui::Begin("Engine's Controls"))
	{
		ImVec4 active_color = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
		ImVec4 inactive_color = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
		ImGui::PushStyleColor(ImGuiCol_Button, showGrid ? active_color : inactive_color);
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.45f, 0.45f, 0.45f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 1.0f, 1.0f));

		// Define a static variable for timing
		static float lastUpdateTime = 0.0f;
		static float displayFrameTime = 0.0f;
		float currentTime = ImGui::GetTime(); // Get current time in seconds

		if (currentTime - lastUpdateTime >= 1.0f) { // Update every second
			displayFrameTime = 1000.0f / ImGui::GetIO().Framerate;
			lastUpdateTime = currentTime;
		}
		// Display the frame time (updated every second)
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", displayFrameTime, ImGui::GetIO().Framerate);
		
		//show/hide grid
		ImGui::Checkbox("Show Grid", &showGrid);
	
		//scene rotoation
		if(ImGui::CollapsingHeader("Scene Rotation"))
		{
			ImGui::SliderFloat("SceneRotationX", &(screenRotation.rotate.x),-360.0f, 360.0f);
			ImGui::SliderFloat("SceneRotationY", &(screenRotation.rotate.y),-360.0f, 360.0f);
			ImGui::SliderFloat("SceneRotationZ", &(screenRotation.rotate.z),-360.0f, 360.0f);
			if (ImGui::Button("Reset Scene Rotation"))  
			{                        
				screenRotation.rotate.x = 9.0f;
				screenRotation.rotate.y = 12.0f;
				screenRotation.rotate.z = 0.0f;
			}
		}

		if(ImGui::CollapsingHeader("Add/Delete Shape"))
		{
			if (ImGui::Button("Triangle"))  
			{                        
				createShape(TRIANGLE);
				scaleAllOffSet = 0.0f;
			}
			ImGui::SameLine();
			if (ImGui::Button("Rectangle")) 
			{                   
				createShape(RECTANGLE);
				scaleAllOffSet = 0.0f;
			}
			ImGui::SameLine();
			if (ImGui::Button("Cube")) 
			{                   
				createShape(CUBE);
				scaleAllOffSet = 0.0f;
			}
			ImGui::SameLine();
			if (ImGui::Button("Sphere"))  
			{                        
				createShape(SPHERE);
				scaleAllOffSet = 0.0f;
			}
			ImGui::SameLine();
			if (ImGui::Button("Cylinder"))  
			{                        
				createShape(CYLINDER);
				scaleAllOffSet = 0.0f;
			}

			if (ImGui::Button("Delete selected Shape"))  
			{    
				deleteShape(selectedShape);
			}
		}

		if(ImGui::CollapsingHeader("Navigation"))
		{
			if (ImGui::Button("Next Shape"))  
			{
				selectedShape = selectedShape->next;
			}
			ImGui::SameLine();
			if (ImGui::Button("Previous Shape"))  
			{    
				selectedShape = selectedShape->pre;
			}
		}

		if(ImGui::CollapsingHeader("Save/Load Scene"))
		{
			// Show the button to open the popup
			static bool show_popup = false;  // Flag to show the popup
			bool saveFileFlag = false;
			if (ImGui::Button("Save File"))
			{
				show_popup = true;  // Set flag to show the popup
			}
			// Call the function to handle the popup
			saveFileFlag = ShowTextInputPopup(&show_popup, input_text, "Enter File Name:", ".csv");	
			if(saveFileFlag == true)
			{
				saveToCSV(input_text, head);
				saveFileFlag = false;
			}

			//load file
			if (ImGui::Button("Load File"))
			{
				loadCSV("resources/scene.csv");
			}
		}

		if(selectedShape != NULL) //means linklist has at least one node
		{	
			if(ImGui::CollapsingHeader("Transformations"))
			{
				//--- TRANSLATE------
				// Draw a colored background for the TreeNode
				if(ImGui::TreeNode("Shape's placement"))
				{
					ImGui::SliderFloat("PositionX", &(selectedShape->shape.position.x), -15.0f, 15.0f);
					ImGui::SliderFloat("PositionY", &(selectedShape->shape.position.y), -15.0f, 15.0f);
					ImGui::SliderFloat("PositionZ", &(selectedShape->shape.position.z), -15.0f, 15.0f);
					ImGui::TreePop();
				}

				//--- SCALE------
				if(ImGui::TreeNode("Shape's Scaling"))
				{
					float beforeScaleAllOffSet = scaleAllOffSet;
					float scaleAllOffSetChanged = 0.0f;
					if(ImGui::SliderFloat("ScaleAll%", &scaleAllOffSet, -400.0f, 400.0f))
					{
						scaleAllOffSetChanged = scaleAllOffSet-beforeScaleAllOffSet;
						selectedShape->shape.scale.x += selectedShape->shape.scale.x * (scaleAllOffSetChanged / 100);
						selectedShape->shape.scale.y += selectedShape->shape.scale.y * (scaleAllOffSetChanged / 100);
						selectedShape->shape.scale.z += selectedShape->shape.scale.z * (scaleAllOffSetChanged / 100);
					}
					ImGui::SliderFloat("ScaleX", &(selectedShape->shape.scale.x), -1.0f, 5.0f);
					ImGui::SliderFloat("ScaleY", &(selectedShape->shape.scale.y), -1.0f, 5.0f);
					ImGui::SliderFloat("ScaleZ", &(selectedShape->shape.scale.z), -1.0f, 5.0f);
					ImGui::TreePop();
				}

				//--- Rotation------
				if(ImGui::TreeNode("Shape's Rotation"))
				{
					ImGui::SliderFloat("RotationX", &(selectedShape->shape.rotationAngle.x), 0.0f, 360.0f);
					ImGui::SliderFloat("RotationY", &(selectedShape->shape.rotationAngle.y), 0.0f, 360.0f);
					ImGui::SliderFloat("RotationZ", &(selectedShape->shape.rotationAngle.z), 0.0f, 360.0f);
					ImGui::TreePop();
				}

				//--- COlor -----
				if(ImGui::TreeNode("Shape's Color"))
				{
					switch (selectedShape->shape.shapetype)
					{
					case CUBE:
						ImGui::ColorEdit3("Color1", (float*)(selectedShape->shape.colors));
						ImGui::ColorEdit3("Color2", (float*)(selectedShape->shape.colors) + 4);
						ImGui::ColorEdit3("Color3", (float*)(selectedShape->shape.colors) + 8);
						ImGui::ColorEdit3("Color4", (float*)(selectedShape->shape.colors) + 12);
						ImGui::ColorEdit3("Color5", (float*)(selectedShape->shape.colors) + 16);
						ImGui::ColorEdit3("Color6", (float*)(selectedShape->shape.colors) + 20);
						break;
					
					default:
						ImGui::ColorEdit3("color", (float*)selectedShape->shape.colors);
						break;
					}

					ImGui::TreePop();
				}
				
				//custom attributes
				if(selectedShape->shape.customShapeAttributes != NULL)
				{
					if(ImGui::TreeNode("Shape's Custom attributes"))
					{
						static bool enableWireframe = false;
						ImGui::Checkbox("Enable Wireframe", &enableWireframe);
						if(enableWireframe == true)
							selectedShape->shape.customShapeAttributes[0]= 0.0f;
						else
							selectedShape->shape.customShapeAttributes[0]= 1.0f;

						if(selectedShape->shape.shapetype == SPHERE)
						{
							ImGui::SliderFloat("Slices", &(selectedShape->shape.customShapeAttributes[1]), 1.0f, 60.0f);
							ImGui::SliderFloat("Stacks", &(selectedShape->shape.customShapeAttributes[2]), 1.0f, 60.0f);
						}
						if(selectedShape->shape.shapetype == CYLINDER)
						{
							ImGui::SliderFloat("1st opening radius", &(selectedShape->shape.customShapeAttributes[1]), 0.0f, 10.0f);
							ImGui::SliderFloat("2nd opening radius", &(selectedShape->shape.customShapeAttributes[2]), 0.0f, 10.0f);
							ImGui::SliderFloat("Length", &(selectedShape->shape.customShapeAttributes[3]), 0.0f, 20.0f);
							ImGui::SliderFloat("Slices", &(selectedShape->shape.customShapeAttributes[4]), 1.0f, 60.0f);
							ImGui::SliderFloat("Stacks", &(selectedShape->shape.customShapeAttributes[5]), 1.0f, 60.0f);
						}
						//ImGui::Text("currently selected shape= %d", selectedShape->shape.shapetype);
						ImGui::TreePop();
					}
				}
			}
		}
		ImGui::PopStyleColor(3);
	}
	ImGui::End();
}


// Function to handle text input popup
bool ShowTextInputPopup(bool *show_popup, char *input_text, char *label, char *input_text_append)
{
	bool textValueReceived = false;
	
    // Popup dialog for text input
    if (*show_popup == true)
    {
        ImGui::OpenPopup(label);
    }

    if (ImGui::BeginPopupModal(label, show_popup, ImGuiWindowFlags_AlwaysAutoResize))
    {
        
        // Text input field
        ImGui::InputText(input_text_append, input_text, MAX_TEXT_INPUT_SIZE,ImGuiInputTextFlags_EnterReturnsTrue);

        // OK and Cancel buttons
        if (ImGui::Button("OK"))
        {
            // Process the input text as needed
			textValueReceived = true;

            *show_popup = false; // Close the popup

			// Ensure input_text has enough space to append input_text_append
			if (strlen(input_text) + strlen(input_text_append) < MAX_TEXT_INPUT_SIZE)
				strcat(input_text, input_text_append);
			else
				printf("Error: Not enough space to append text in file name.\n");
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
			textValueReceived = false;

            *show_popup = false; // Close the popup without processing input
        }

        ImGui::EndPopup();
    }

	return textValueReceived;
}

