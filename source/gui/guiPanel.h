#ifndef GUIPANEL_H
#define GUIPANEL_H

#include "general.h"
#include "guiElement.h"

class guiPanel : public guiElement
{
    public:
        guiPanel(int id = -1) : guiElement(id,GUI_PANEL){}
        virtual ~guiPanel(){}

    public:
        virtual void draw();

        virtual void onEnter(){}
        virtual void onExit(){}
        virtual void onMouseDown(){}
        virtual void onMouseUp(){}
        virtual void onDragExit(){}
        virtual void onDragEnter(){}
};

#endif // GUIPANEL_H
