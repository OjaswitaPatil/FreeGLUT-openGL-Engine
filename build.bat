::clean
cls
del *.csv
for /r %%i in (*.obj) do del "%%i"
for /r %%i in (*.exe) do del "%%i"
echo Cleaning completed!


:: Compilation: to create .obj files in the same directory as the respective .cpp files
for %%f in (OGL.cpp Shape.cpp imGuiExtenstion.cpp LinkedList.cpp SaveAndLoadCSV.cpp imgui\*.cpp) do (
    cl.exe /c /EHsc /I C:\freeglut\include /I "C:\MyProjects\99-MyWork\03-Engine\OJuEnginePractice\imGUI" "%%f" /Fo"%%~dpf%%~nf.obj"
)

:: Linking: To create the .exe file
link.exe OGL.obj Shape.obj imGuiExtenstion.obj LinkedList.obj SaveAndLoadCSV.obj imgui\imgui.obj imgui\imgui_demo.obj imgui\imgui_draw.obj imgui\imgui_tables.obj imgui\imgui_widgets.obj imgui\imgui_impl_glut.obj imgui\imgui_impl_opengl2.obj /LIBPATH:C:\freeglut\lib\x64 freeglut.lib opengl32.lib glu32.lib /SUBSYSTEM:CONSOLE

