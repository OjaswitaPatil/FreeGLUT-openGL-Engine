#ifndef IMGUIEXTENSION_H
#define IMGUIEXTENSION_H

//header files
#include "globalHeaders.h"
//IMGUI related header files
#include "imGUI/imgui.h"
#include "imGUI/imgui_impl_glut.h"
#include "imGUI/imgui_impl_opengl2.h"
#include "shape.h"
#include "LinkedList.h"
#include "SaveAndLoadCSV.h"
#define GL_SILENCE_DEPRECATION

#define MAX_TEXT_INPUT_SIZE 256

//global variables
extern bool showGrid;
extern char input_text[MAX_TEXT_INPUT_SIZE];

//function prototypes
void imGuiInitialization(void);
void updateimGuiDisplaySize(int width, int height);
void startimGuiFrame(void);
void renderimGui(void);
void setupMouseClickInimGui(int button, int state, int x, int y);
void setupMouseMotionInimGui(int x, int y);
void imGuiUninitialization(void);

void renderimGUIControls(void);
bool ShowTextInputPopup(bool *show_popup, char *input_text, char *label, char *input_text_append);


#endif 

