#ifndef GUILABEL_H
#define GUILABEL_H

#include "guiElement.h"
#include "Font.h"

class guiLabel : public guiElement
{
    public:
        guiLabel(int id = -1) : guiElement(id,GUI_LABEL){}
        virtual ~guiLabel(){}

    public:
        Font*   font = nullptr;
        virtual void draw();

        virtual void onEnter(){}
        virtual void onExit(){}
        virtual void onMouseDown(){}
        virtual void onMouseUp(){}
        virtual void onDragExit(){}
        virtual void onDragEnter(){}
};

#endif // GUILABEL_H
