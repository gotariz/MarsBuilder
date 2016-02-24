#ifndef OPENGLAPP_H
#define OPENGLAPP_H

#include "general.h"
#include "gui/guiManager.h"
#include "gui/guiPanel.h"
#include "gui/guiButton.h"
#include "gui/font.h"
#include "modules/Module.h"
#include "modules/modLowGrade.h"
#include "modules/modHighGrade.h"
#include "modules/modLowGradeDoor.h"
#include "modules/modHighGradeDoor.h"
#include "modules/modLowGradeWindow.h"
#include "modules/modHighGradeWindow.h"
#include "modules/modInternalWall.h"
#include "modules/modInternalDoor.h"
#include "modules/modConnectingDoor.h"
#include "modules/modCorridor.h"
#include "modules/modAirLockDoor.h"
#include "modules/modAccessory.h"

void glCallback_reshape(int width, int height);
void glCallback_display();
void glCallback_motion(int x, int y);
void glCallback_passiveMotion(int x, int y);
void glCallback_mouse(int button, int state, int x, int y);
void glCallback_special(int key, int x, int y);
void glCallback_keyboard(unsigned char key, int x, int y);

class OpenGLApp
{
    public:
        OpenGLApp(){}
        virtual ~OpenGLApp(){}

    public:
        guiManager  gManager;
        Font        font;
        float       zoom = 1;
        int         tool = -1;

        Module*     mod = nullptr;
        Point       offset;
        Point       originalPos;
        Point       originalSize;
        int         originalOrientation = HORIZONTAL;

        std::vector<Module*>        modules;
        std::vector<UndoEvent>      undos;
    public:
        void initGlobals();
        void initOpenGL(int argc, char** argv);
        void initGUI();

        void runApp();
        void freeResources();

        void drawGUI();
        void drawCanvas();
        void drawGrid();
        void drawCrosshair();
        void drawModules();

        void switchDrawSpace(DrawSpace drawspace);
        void handleGuiEvents();

        void mousePressedCanvas();
        void mouseReleasedCanvas();

    public: // utilities
        void deleteAllModules();
        void deleteModule(Module* m);
        void removeModule(Module* m);
        void undoLastAction();
        void zoomIn();
        void zoomOut();

        void saveToFile(std::string path);
        void openFromFile(std::string path);

        Module* getHoveredModule(Point p, bool movable);
        Module* createModule(int type);
};

#endif // OPENGLAPP_H
