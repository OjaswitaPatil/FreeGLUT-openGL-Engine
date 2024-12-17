::clean folder
cls
del OGL.obj
del OGL.exe

::compililation: to create obj files
cl.exe /c /EHsc /I C:\freeglut\include OGL.c shape.c

::Linking: To create exe file
link.exe OGL.obj shape.obj /LIBPATH:C:\freeglut\lib\x64 freeglut.lib /SUBSYSTEM:CONSOLE   
 