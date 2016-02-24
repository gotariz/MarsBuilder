#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include "glib.h"
#include "structs.h"
#include "dependencies.h"

using namespace glib;
class OpenGLApp;
class Font;

class Globals {
    public:

        // pointers
        OpenGLApp*  app         = nullptr;
        Font*       fontNormal  = nullptr;

        // rectangles
        Rec rCameraCanvas;      // camera rectangle for the canvas
        Rec rCamera;            // camera rectangle for the entire screen
        Rec rCanvas;            // viewport for the canvas
        Rec rScreen;            // viewport for the screen

        Point mPosition;
        Point mPositionWorld;
        Point crosshair;
};

extern Globals globals;


#endif // GLOBALS_H_INCLUDED
