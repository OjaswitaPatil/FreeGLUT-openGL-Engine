#ifndef IMGUIEXTENSION_H
#define IMGUIEXTENSION_H

//header files
#include "globalHeaders.h"
//IMGUI related header files
#include "imGUI/imgui.h"
#include "imGUI/imgui_impl_glut.h"
#include "imGUI/imgui_impl_opengl2.h"
#define GL_SILENCE_DEPRECATION

//function prototypes
void imGuiInitialization(void);
void updateimGuiDisplaySize(int width, int height);
void startimGuiFrame(void);
void renderimGui(void);
void setupMouseClickInimGui(int button, int state, int x, int y);
void setupMouseMotionInimGui(int x, int y);
void imGuiUninitialization(void);

#endif 

