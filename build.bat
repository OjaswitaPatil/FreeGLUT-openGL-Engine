::clean
cls
del OGL.obj
del OGL.exe

::compililation: to create obj files
cl.exe /c /EHsc /I C:\freeglut\include OGL.c

::Linking: To create exe file
link.exe OGL.obj /LIBPATH:C:\freeglut\lib\x64 freeglut.lib /SUBSYSTEM:CONSOLE   
