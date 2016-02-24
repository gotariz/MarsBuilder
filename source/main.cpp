#include <GL/glut.h>
#include <stdlib.h>

#include "general.h"
#include "OpenGLApp.h"


int main(int argc, char** argv)
{
    OpenGLApp   tomsApp;

    tomsApp.initGlobals();
    tomsApp.initOpenGL(argc, argv);
    tomsApp.initGUI();
    tomsApp.runApp();
    tomsApp.freeResources();

    return 0;
}
