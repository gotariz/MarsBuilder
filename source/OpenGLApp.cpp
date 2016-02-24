#include "OpenGLApp.h"

///////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
///////////////////////////////////////////////////////////////////////////////
void OpenGLApp::freeResources()
{
    gManager.freeResources();
    // TODO: free modules etc... resources
    for (unsigned i = 0; i < modules.size(); ++i)
    {
        delete modules.at(i);
        modules.at(i) = nullptr;
    }

    modules.clear();
}

void OpenGLApp::runApp()
{
    glutMainLoop();
}

///////////////////////////////////////////////////////////////////////////////
// INIT FUNCTIONS
///////////////////////////////////////////////////////////////////////////////
void OpenGLApp::initGlobals()
{
    globals.app = this;

    globals.rScreen.set(0,0,DEFAULT_WIDTH,DEFAULT_HEIGHT);
    globals.rCanvas.set(TOOLBARSIZE,0,DEFAULT_WIDTH-TOOLBARSIZE,DEFAULT_HEIGHT-TOOLBARSIZE);

    globals.rCamera.set(0,0,DEFAULT_WIDTH,DEFAULT_HEIGHT);
    globals.rCameraCanvas.set(0,0,DEFAULT_WIDTH-TOOLBARSIZE,DEFAULT_HEIGHT-TOOLBARSIZE);

    // cannot create font's here because we havn't initialised openGL yet
}

void OpenGLApp::initOpenGL(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_MULTISAMPLE);
    glutInitWindowSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("COMP330 Assignment 1");

    // assign callback functions
    glutDisplayFunc(glCallback_display);
    glutReshapeFunc(glCallback_reshape);
    glutMotionFunc(glCallback_motion);
    glutPassiveMotionFunc(glCallback_passiveMotion);
    glutMouseFunc(glCallback_mouse);
    glutKeyboardFunc(glCallback_keyboard);
    glutSpecialFunc(glCallback_special);

    // Define world window and set up window-to-viewport transformation
    glMatrixMode(GL_PROJECTION);        // Set the projection matrix
    glLoadIdentity();                   // Initialise to identity matrix
    gluOrtho2D(0.0, globals.rCamera.w, 0.0, globals.rCamera.h); // Set to orthographic projection of window

    glClearColor(C_WHITE.r,C_WHITE.g,C_WHITE.b,C_WHITE.a);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLApp::initGUI()
{
    font.loadFont("media/fonts/purista-medium-14-white/");
    font.setColour(C_BLACK);
    globals.fontNormal = &font;

    // the top gui panel
    guiPanel* toolbar = gManager.createPanel();
    toolbar->m_colour = C_DARK_GREY;
	toolbar->setAnchor(TOP,LEFT);
	toolbar->m_relative_w.set(true,100.f);
	toolbar->m_size.set(0,TOOLBARSIZE);
	toolbar->m_position.set(0,TOOLBARSIZE);

    // the left gui panel
    guiPanel* toolbox = gManager.createPanel();
    toolbox->m_colour = C_DARK_GREY;
    toolbox->m_relative_h.set(true,100.f);
    toolbox->m_size.set(TOOLBARSIZE,-TOOLBARSIZE);
    toolbox->m_position.set(0,0);

    // the label displaying the current zoom value
    guiLabel* label = gManager.createLabel(LBL_ZOOM);
    label->m_position.set(178,23);
    label->setAnchor(TOP,LEFT);
    label->text = "100%";
    label->font = &font;

    // button id's and their image to load
    std::vector<Pair>           buttons;
    buttons.push_back(Pair(BTN_M    ,"media/images/btn_move") );
    buttons.push_back(Pair(BTN_R    ,"media/images/btn_resize") );
    buttons.push_back(Pair(BTN_MH   ,"media/images/btn_module_high"));
    buttons.push_back(Pair(BTN_ML   ,"media/images/btn_module_low"));
    buttons.push_back(Pair(BTN_DH   ,"media/images/btn_door_high"));
    buttons.push_back(Pair(BTN_DL   ,"media/images/btn_door_low"));
    buttons.push_back(Pair(BTN_DAL  ,"media/images/btn_door_pressure"));
    buttons.push_back(Pair(BTN_DC   ,"media/images/btn_door_connecting"));
    buttons.push_back(Pair(BTN_DI   ,"media/images/btn_door_internal"));
    buttons.push_back(Pair(BTN_WI   ,"media/images/btn_wall_internal"));
    buttons.push_back(Pair(BTN_WH   ,"media/images/btn_window_high"));
    buttons.push_back(Pair(BTN_WL   ,"media/images/btn_window_low"));
    buttons.push_back(Pair(BTN_C    ,"media/images/btn_corridor"));

    for (unsigned i = 0; i < buttons.size(); ++i) {
        guiButton* btn = gManager.createButton(buttons.at(i).id);
        btn->m_img.loadFromFile(buttons.at(i).path + ".png");
        btn->m_size.set(ICONSIZE,ICONSIZE);
        btn->m_position.set(0,64 + (ICONSIZE * i));
        btn->setAnchor(TOP,LEFT);
        btn->m_isToggle = true;
    }

    std::vector<Pair>   buttons2;
    buttons2.push_back( Pair(BTN_UNDO,"media/images/btn_undo") );
    buttons2.push_back( Pair(BTN_SAVE,"media/images/btn_save") );
    buttons2.push_back( Pair(BTN_OPEN,"media/images/btn_open") );
    buttons2.push_back( Pair(BTN_ZO,"media/images/btn_zoom_out") );
    buttons2.push_back( Pair(BTN_ZI,"media/images/btn_zoom_in") );

    for (unsigned i = 0; i < buttons2.size(); ++i) {
        guiButton* btn = gManager.createButton(buttons2.at(i).id);
        btn->m_img.loadFromFile(buttons2.at(i).path + ".png");
        btn->m_size.set(ICONSIZE,ICONSIZE);
        btn->m_position.set(ICONSIZE + (ICONSIZE * (i == 4 ? 6 : i)),ICONSIZE);
        btn->setAnchor(TOP,LEFT);
        btn->m_isToggle = false;
    }

    std::vector<Pair>   accossories;
    accossories.push_back( Pair(BTN_BATH,"media/images/btn_bath") );
    accossories.push_back( Pair(BTN_BED,"media/images/btn_bed") );
    accossories.push_back( Pair(BTN_COUNTER,"media/images/btn_counter") );
    accossories.push_back( Pair(BTN_SHOWER,"media/images/btn_shower") );
    accossories.push_back( Pair(BTN_SINK,"media/images/btn_sink") );
    accossories.push_back( Pair(BTN_STOVE,"media/images/btn_stove") );
    accossories.push_back( Pair(BTN_TABLE,"media/images/btn_table") );
    accossories.push_back( Pair(BTN_TOILET,"media/images/btn_toilet") );
    accossories.push_back( Pair(BTN_WARDROBE,"media/images/btn_wardrobe") );

    for (unsigned i = 0; i < accossories.size(); ++i) {
        guiButton* btn = gManager.createButton(accossories.at(i).id);
        btn->m_img.loadFromFile(accossories.at(i).path + ".png");
        btn->m_size.set(ICONSIZE,ICONSIZE);
        btn->m_position.set(ICONSIZE + (ICONSIZE * (i + 10)),ICONSIZE);
        btn->setAnchor(TOP,LEFT);
        btn->m_isToggle = true;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Utilities
///////////////////////////////////////////////////////////////////////////////
Module* OpenGLApp::getHoveredModule(Point p, bool movable)
{
    for (int i = modules.size()-1; i >= 0; --i) {
        if (movable) {  // get movable module
            if (modules.at(i)->movable and modules.at(i)->isTouching(p))    return modules.at(i);
        } else {        // get resizable module
            if (modules.at(i)->resizable and modules.at(i)->isTouching(p))  return modules.at(i);
        }
    }

    return nullptr;
}

void OpenGLApp::deleteAllModules()
{
    for (int i = modules.size()-1; i >= 0; --i) {
        // this will create a problem if there are multiple of the same module.
        // there should not be a case where there are multiple modules though
        delete modules.at(i);
        modules.erase(modules.begin() + i);
    }
}

void OpenGLApp::deleteModule(Module* m)
{
    for (int i = modules.size()-1; i >= 0; --i) {
        if (modules.at(i) == m) {
            delete modules.at(i);
            modules.erase(modules.begin() + i);
        }
    }
}

void OpenGLApp::removeModule(Module* m)
{
    for (int i = modules.size()-1; i >= 0; --i) {
        if (modules.at(i) == m) modules.erase(modules.begin() + i);
    }
}

void OpenGLApp::undoLastAction()
{
    if (undos.size() == 0) return;

    UndoEvent e = undos.back();
    undos.pop_back();

    if (e.type == CREATION) {
        // remove the module
        deleteModule(e.module);
    } else if (e.type == MOVED) {
        e.module->setPosition(e.oldPosition);
        e.module->setOrientation(e.oldOrientation);
        e.module->calibrate();
    } else if (e.type == RESIZED) {
        e.module->setSize(e.oldSize);
        e.module->setPosition(e.oldPosition);
        e.module->setOrientation(e.oldOrientation);
        e.module->calibrate();
    }
}

void OpenGLApp::zoomIn()
{
    zoom -= ZOOM_INCREMENT;
    globals.app->zoom = std::max(globals.app->zoom,0.1f);
    glCallback_reshape(globals.rScreen.w,globals.rScreen.h);
    glCallback_passiveMotion(globals.mPosition.x,globals.rScreen.h - globals.mPosition.y);
    float pzoom = (static_cast<float>(globals.rCameraCanvas.w) / static_cast<float>(globals.rCanvas.w)) * 100.f;
    gManager.getElementByID(LBL_ZOOM)->text = toString(utils::roundNearestf(pzoom,1)) + "%";
    glCallback_display();
}

void OpenGLApp::zoomOut()
{
    zoom += ZOOM_INCREMENT;
    globals.app->zoom = std::min(globals.app->zoom,5.f);
    glCallback_reshape(globals.rScreen.w,globals.rScreen.h);
    glCallback_passiveMotion(globals.mPosition.x,globals.rScreen.h - globals.mPosition.y);
    float pzoom = (static_cast<float>(globals.rCameraCanvas.w) / static_cast<float>(globals.rCanvas.w)) * 100.f;
    gManager.getElementByID(LBL_ZOOM)->text = toString(utils::roundNearestf(pzoom,1)) + "%";
    glCallback_display();
}

///////////////////////////////////////////////////////////////////////////////
// Events
///////////////////////////////////////////////////////////////////////////////

void OpenGLApp::handleGuiEvents()
{
    guiEvent event;

    while (gManager.pollEvent(event)) {
        if (event.state == CLICKED) {
            if (event.id == BTN_ZI)         zoomIn();
            else if (event.id == BTN_ZO)    zoomOut();
            else if (event.id == BTN_UNDO)  undoLastAction();
            else if (event.id == BTN_SAVE)  saveToFile("MartianHouse.xml");
            else if (event.id == BTN_OPEN)  openFromFile("MartianHouse.xml");

        } else if (event.state == TOGGLED_ON) {
            tool = event.id;
        } else if (event.state == TOGGLED_OFF) {
            tool = -1;
        }
    }
}

void OpenGLApp::mousePressedCanvas()
{
    if (mod != nullptr)    delete mod;

    Module* m = nullptr;

    if (tool == BTN_ML)         m = new modLowGrade();
    else if (tool == BTN_MH)    m = new modHighGrade();
    else if (tool == BTN_DL)    m = new modLowGradeDoor();
    else if (tool == BTN_DH)    m = new modHighGradeDoor();
    else if (tool == BTN_WL)    m = new modLowGradeWindow();
    else if (tool == BTN_WH)    m = new modHighGradeWindow();
    else if (tool == BTN_WI)    m = new modInternalWall();
    else if (tool == BTN_DI)    m = new modInternalDoor();
    else if (tool == BTN_DC)    m = new modConnectingDoor();
    else if (tool == BTN_C)     m = new modCorridor();
    else if (tool == BTN_DAL)   m = new modAirLockDoor();
    else if (tool == BTN_TABLE)     {m = new modAccessory();m->setName("TABLE");m->setModuleType(M_ACCESSORY_TABLE);}
    else if (tool == BTN_BED)       {m = new modAccessory();m->setName("BED");m->setModuleType(M_ACCESSORY_BED);}
    else if (tool == BTN_SHOWER)    {m = new modAccessory();m->setName("SHOWER");m->setModuleType(M_ACCESSORY_SHOWER);}
    else if (tool == BTN_BATH)      {m = new modAccessory();m->setName("BATH");m->setModuleType(M_ACCESSORY_BATH);}
    else if (tool == BTN_WARDROBE)  {m = new modAccessory();m->setName("WARDROBE");m->setModuleType(M_ACCESSORY_WARDROBE);}
    else if (tool == BTN_SINK)      {m = new modAccessory();m->setName("SINK");m->setModuleType(M_ACCESSORY_SINK);}
    else if (tool == BTN_STOVE)     {m = new modAccessory();m->setName("STOVE");m->setModuleType(M_ACCESSORY_STOVE);}
    else if (tool == BTN_COUNTER)   {m = new modAccessory();m->setName("COUNTER");m->setModuleType(M_ACCESSORY_COUNTER);}
    else if (tool == BTN_TOILET)    {m = new modAccessory();m->setName("TOILET");m->setModuleType(M_ACCESSORY_TOILET);}
    else if (tool == BTN_M) {
        Point p = utils::getMouseWorldCoordinatesCanvas(globals.mPosition.x,globals.mPosition.y);

        mod = getHoveredModule(p,true);
        if (mod == nullptr) return; // didn't click on a module

        removeModule(mod);
        originalPos         = mod->getPosition();
        originalSize        = mod->getSize();
        originalOrientation = mod->getOrientation();
        offset              = globals.crosshair.subtracted(originalPos);

    } else if (tool == BTN_R) {
        Point p = utils::getMouseWorldCoordinatesCanvas(globals.mPosition.x,globals.mPosition.y);

        mod = getHoveredModule(p,false);
        if (mod == nullptr) return; // didn't click on a module

        removeModule(mod);
        originalPos         = mod->getPosition();
        originalSize        = mod->getSize();
        originalOrientation = mod->getOrientation();
        offset              = globals.crosshair.subtracted(originalPos);

        // all the corners of the object
        Point bl = Point(originalPos.x,originalPos.y);                                  // bottom left corner
        Point tr = Point(originalPos.x+originalSize.x,originalPos.y+originalSize.y);    // top right corner
        Point tl = Point(bl.x,tr.y);                                                    // top left corner
        Point br = Point(tr.x,bl.y);                                                    // bottom right corner

        Point c;    // the corner closest to the mouse
        c.x = std::abs(p.x - bl.x) < std::abs(p.x - tr.x) ? bl.x : tr.x;
        c.y = std::abs(p.y - bl.y) < std::abs(p.y - tr.y) ? bl.y : tr.y;

        // set p1(the anchor point) to be the opposite of the point being dragged
        if (c == bl)        mod->setP1(tr);
        else if (c == br)   mod->setP1(tl);
        else if (c == tr)   mod->setP1(bl);
        else                mod->setP1(br);
        mod->setP2(c);
    }

    if (m != nullptr)
    {
        m->setP1(globals.crosshair.x,globals.crosshair.y);
        m->setP2(globals.crosshair.x,globals.crosshair.y);
        m->calculatePositionAndSize();
        m->calibrate();
        mod = m;
    }
}

void OpenGLApp::mouseReleasedCanvas()
{
    if (mod != nullptr) {
        if (tool == BTN_M) {    // completing a move operation
            bool moved = true;
            if (!mod->isValidPosition(modules)) // the modification was invalid, revert to previous
            {
                mod->setPosition(originalPos);
                mod->setOrientation(originalOrientation);
                mod->calibrate();
                moved = false;
            }
            if (moved) { // create an undo event
                UndoEvent e = UndoEvent(MOVED,mod);
                e.oldOrientation = originalOrientation;
                e.oldPosition = originalPos;
                undos.push_back(e);
            }
            modules.push_back(mod);
            mod = nullptr;
        } else if (tool == BTN_R) { // completing a resize operation
            bool resized = true;
            if (!mod->isValid() or !mod->isValidPosition(modules))  // the modification was invalid, revert to previous
            {
                mod->setPosition(originalPos);
                mod->setSize(originalSize);
                mod->setOrientation(originalOrientation);
                mod->calibrate();
                resized = false;
            }
            if (resized) { // create an undo event
                UndoEvent e = UndoEvent(RESIZED,mod);
                e.oldOrientation = originalOrientation;
                e.oldPosition = originalPos;
                e.oldSize = originalSize;
                undos.push_back(e);
            }
            modules.push_back(mod);
            mod = nullptr;
        } else {    // completeing a creation operation
            if (mod->isValid() and mod->isValidPosition(modules))
            {
                undos.push_back(UndoEvent(CREATION,mod));
                modules.push_back(mod);
                mod = nullptr;
            } else {
                // the object was position or size was invalid. Delete it
                std::cout << "deleted" << std::endl;
                delete mod;
                mod = nullptr;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Draw Functions
///////////////////////////////////////////////////////////////////////////////
void OpenGLApp::switchDrawSpace(DrawSpace drawspace)
{
    Rec rec_camera;
    Rec rec_viewport;

    if (drawspace == SCREEN) {                  // we want to be able to draw onto the screen directly
        rec_viewport    = globals.rScreen;
        rec_camera      = globals.rCamera;
    } else if (drawspace == CANVAS) {           // we want to be able to draw onto the world
        rec_viewport    = globals.rCanvas;
        rec_camera      = globals.rCameraCanvas;
    }

    glViewport(rec_viewport.x, rec_viewport.y, rec_viewport.w, rec_viewport.h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(
               rec_camera.x,                    // x1 pos
               rec_camera.x+rec_camera.w,       // x2 pos
               rec_camera.y,                    // y1 pos
               rec_camera.y+rec_camera.h);      // y2 pos
}

void OpenGLApp::drawGUI()
{
    gManager.draw();
    drawCrosshair();
}

void OpenGLApp::drawCanvas()
{
    drawGrid();
    drawModules();

    if (mod != nullptr) // the modules being created or modified
        mod->render();
}

void OpenGLApp::drawGrid()
{
    // the position fo the first horizontal and vertical line to draw
    int start_x = utils::roundUp(globals.rCameraCanvas.x, GRID_SIZE);
    int start_y = utils::roundUp(globals.rCameraCanvas.y, GRID_SIZE);

    // horizontal lines
    while (start_y < globals.rCameraCanvas.y + globals.rCameraCanvas.h) {
        // draw origin lines different colours
        if (start_y == 0)   glSetColour(C_X_AXIS);
        else                glSetColour(C_GRID);

        glBegin(GL_LINES);
            glVertex2f(globals.rCameraCanvas.x,start_y);
            glVertex2f(globals.rCameraCanvas.x + globals.rCameraCanvas.w,start_y);
        glEnd();

        start_y += GRID_SIZE;
    }

    // vertical lines
    while (start_x < globals.rCameraCanvas.x + globals.rCameraCanvas.w) {
        // draw origin lines different colours
        if (start_x == 0)   glSetColour(C_Y_AXIS);
        else                glSetColour(C_GRID);

        glBegin(GL_LINES);
            glVertex2f(start_x,globals.rCameraCanvas.y);
            glVertex2f(start_x,globals.rCameraCanvas.y + globals.rCameraCanvas.h);
        glEnd();

        start_x += GRID_SIZE;
    }
}

void OpenGLApp::drawModules()
{
    for (unsigned i = 0; i < modules.size(); ++i) {
        Module* m = modules.at(i);
        m->render();
    }
}


void OpenGLApp::drawCrosshair()
{
    // get the world position of the crosshair
    Point cp = utils::getCrosshairWorldPosition(globals.mPositionWorld.x,globals.mPositionWorld.y);
    cp = utils::worldToCanvas(cp.x,cp.y);

    // we are drawing the crosshair onto the screen not the canvas so we need to add the canvas x and y position
    cp.x += globals.rCanvas.x;
    cp.y += globals.rCanvas.y;

    // if the crosshair is located off the canvas don't draw it
    if (cp.x > 32 and cp.y < globals.rCanvas.h) {
        glColor3f(0.f,0.f,0.f);
        glBegin(GL_LINES);
            glVertex2f(cp.x-CROSSHAIRSIZE,cp.y);
            glVertex2f(cp.x + CROSSHAIRSIZE-1,cp.y);
            glVertex2f(cp.x,cp.y-CROSSHAIRSIZE);
            glVertex2f(cp.x,cp.y+CROSSHAIRSIZE-1);
        glEnd();
    }
}

///////////////////////////////////////////////////////////////////////////////
// CALLBACK FUNCTION
///////////////////////////////////////////////////////////////////////////////
void glCallback_reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    // update the rectangles
    globals.rCameraCanvas.setSize((width-TOOLBARSIZE)*globals.app->zoom,(height-TOOLBARSIZE)*globals.app->zoom);
    globals.rCamera.setSize(width,height);
    globals.rCanvas.setSize(width-TOOLBARSIZE,height-TOOLBARSIZE);
    globals.rScreen.setSize(width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(
               globals.rCamera.x,            // x1 pos
               globals.rCamera.x+width,      // x2 pos
               globals.rCamera.y,            // y1 pos
               globals.rCamera.y+height);    // y2 pos

    globals.app->gManager.updateGUIElements();
}

void glCallback_display()
{
    // clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // switch to canvas camera and draw
    globals.app->switchDrawSpace(CANVAS);
    globals.app->drawCanvas();

    // switch to screen camera and draw
    globals.app->switchDrawSpace(SCREEN);
    globals.app->drawGUI();

    glFlush();
}

void glCallback_motion(int x, int y)
{
    globals.mPosition       = utils::glGetMouseCoordinates(x,y);
    globals.mPositionWorld  = utils::getMouseWorldCoordinatesCanvas(globals.mPosition.x,globals.mPosition.y);
    globals.crosshair       = utils::getCrosshairWorldPosition(globals.mPositionWorld.x,globals.mPositionWorld.y);

    if (globals.app->mod != nullptr)
    {
        if (globals.app->tool == BTN_M) {
            globals.app->mod->setPosition( globals.crosshair.subtracted(globals.app->offset) );
            globals.app->mod->calibrate();
        } else {
            globals.app->mod->setP2(globals.crosshair);
            globals.app->mod->calculatePositionAndSize();
            globals.app->mod->calibrate();
        }
    }

    globals.app->gManager.handleMouseDragEvents(globals.mPosition.x,globals.mPosition.y);
    glCallback_display();
}

void glCallback_passiveMotion(int x, int y)
{
    globals.mPosition       = utils::glGetMouseCoordinates(x,y);
    globals.mPositionWorld  = utils::getMouseWorldCoordinatesCanvas(globals.mPosition.x,globals.mPosition.y);
    globals.crosshair       = utils::getCrosshairWorldPosition(globals.mPositionWorld.x,globals.mPositionWorld.y);

    globals.app->gManager.handleMouseMoveEvents(globals.mPosition.x,globals.mPosition.y);
    glCallback_display();
}

void glCallback_mouse(int button, int state, int x, int y)
{
    glib::Point p = utils::glGetMouseCoordinates(x,y);

    // update mouse states
    if (button == MOUSE_LEFT) {
        // only if the mouse is on the canvas
        if (utils::isContained(globals.mPosition,globals.rCanvas))
        {
            if (state == PRESSED)
            {
                globals.app->mousePressedCanvas();
            } else {
                globals.app->mouseReleasedCanvas();
            }
        }

    } else if (button == MOUSE_RIGHT) {
        if (state == PRESSED)
        {
            if (globals.app->mod != nullptr)
            {
                globals.app->mod->rotate();
            }
        }
    }

    globals.app->gManager.handleMouseClickEvents(button,state,p.x,p.y);
    globals.app->handleGuiEvents();
    glCallback_display();
}

void glCallback_special(int key, int x, int y)
{
    int left    = 100;
    int up      = 101;
    int right   = 102;
    int down    = 103;

    if (key == left) {
        globals.rCameraCanvas.translate(-20,0);
    } else if (key == up) {
        globals.rCameraCanvas.translate(0,20);
    } else if (key == right) {
        globals.rCameraCanvas.translate(20,0);
    } else if (key == down) {
        globals.rCameraCanvas.translate(0,-20);
    }

    glCallback_passiveMotion(globals.mPosition.x,globals.rScreen.h - globals.mPosition.y);
    glCallback_display();
}

void glCallback_keyboard(unsigned char key, int x, int y)
{
    if (key == '+') {           // zoom in
        globals.app->zoomIn();
    } else if (key == '-') {
        globals.app->zoomOut(); // zoom out
    }
}

void OpenGLApp::saveToFile(std::string path)
{
    utils::print("saving...");
    XMLDocument doc;
    XMLNode* root = doc.NewElement("modules");
    doc.InsertFirstChild(root);

    for (unsigned i = 0; i < modules.size(); ++i)
    {
        Module* m = modules.at(i);
        XMLElement* element = doc.NewElement("module");

        element->SetAttribute("type",m->getModuleType());
        element->SetAttribute("x",m->getPosition().x);
        element->SetAttribute("y",m->getPosition().y);
        element->SetAttribute("w",m->getSize().x);
        element->SetAttribute("h",m->getSize().y);
        element->SetAttribute("orientation",m->getOrientation());
        root->InsertEndChild(element);
    }


    // ignore the result for now
    XMLError result = doc.SaveFile(path.c_str());
    if (result == XML_SUCCESS)	utils::print("saved.");
    else 						utils::print("Error Saving file.");
}

void OpenGLApp::openFromFile(std::string path)
{
    utils::print("Loading File...");
    XMLDocument doc;
    XMLError result = doc.LoadFile(path.c_str());

    if (result != XML_SUCCESS)
    {
        utils::print("Error loadin save file.");
    }

    XMLNode* root = doc.FirstChild();

    if (root == nullptr)
    {
        utils::print("Error loading save file.");
        return;
    }

    XMLElement* element = root->FirstChildElement("module");
    if (root == nullptr)
    {
        utils::print("Save file is empty.");
        return;
    }


    deleteAllModules();
    while(element != nullptr)
    {
        int type = 0;
        int orientation = 0;
        int x = 0;
        int y = 0;
        int w = 0;
        int h = 0;

        result = element->QueryIntAttribute("type",&type);
        if (result != XML_SUCCESS){utils::print("Error loading module."); continue;}
        result = element->QueryIntAttribute("x",&x);
        if (result != XML_SUCCESS){utils::print("Error loading module."); continue;}
        result = element->QueryIntAttribute("y",&y);
        if (result != XML_SUCCESS){utils::print("Error loading module."); continue;}
        result = element->QueryIntAttribute("w",&w);
        if (result != XML_SUCCESS){utils::print("Error loading module."); continue;}
        result = element->QueryIntAttribute("h",&h);
        if (result != XML_SUCCESS){utils::print("Error loading module."); continue;}
        result = element->QueryIntAttribute("orientation",&orientation);
        if (result != XML_SUCCESS){utils::print("Error loading module."); continue;}

        Module* m = createModule(type);
        if (m != nullptr)
        {
            m->setPosition(x,y);
            m->setSize(w,h);
            m->setOrientation(orientation);
            m->calibrate();
            modules.push_back(m);
        }

        element = element->NextSiblingElement("module");
    }

    utils::print("Finished Loading File.");
}


Module* OpenGLApp::createModule(int type)
{
    Module* m = nullptr;
    if (type == M_INTERNAL_DOOR)                        m = new modInternalDoor();
    else if (type == M_INTERNAL_WALL)                   m = new modInternalWall();
    else if (type == M_CORRIDOR)                        m = new modCorridor();
    else if (type == M_HIGH_GRADE_AIR_LOCK_DOOR)        m = new modAirLockDoor();
    else if (type == M_HIGH_GRADE_CONNTECTING_DOOR)     m = new modConnectingDoor();
    else if (type == M_HIGH_GRADE)                      m = new modHighGrade();
    else if (type == M_HIGH_GRADE_DOOR)                 m = new modHighGradeDoor();
    else if (type == M_HIGH_GRADE_WINDOW)               m = new modHighGradeWindow();
    else if (type == M_LOW_GRADE_WINDOW)                m = new modLowGradeWindow();
    else if (type == M_LOW_GRADE_DOOR)                  m = new modLowGradeDoor();
    else if (type == M_LOW_GRADE)                       m = new modLowGrade();

    else if (type == M_ACCESSORY_TABLE)                 {m = new modAccessory();m->setName("TABLE");}
    else if (type == M_ACCESSORY_BED)                   {m = new modAccessory();m->setName("BED");}
    else if (type == M_ACCESSORY_SHOWER)                {m = new modAccessory();m->setName("SHOWER");}
    else if (type == M_ACCESSORY_BATH)                  {m = new modAccessory();m->setName("BATH");}
    else if (type == M_ACCESSORY_WARDROBE)              {m = new modAccessory();m->setName("WARDROBE");}
    else if (type == M_ACCESSORY_SINK)                  {m = new modAccessory();m->setName("SINK");}
    else if (type == M_ACCESSORY_COUNTER)               {m = new modAccessory();m->setName("COUNTER");}
    else if (type == M_ACCESSORY_STOVE)                 {m = new modAccessory();m->setName("STOVE");}
    else if (type == M_ACCESSORY_TOILET)                {m = new modAccessory();m->setName("TOILET");}

    return m;
}





























