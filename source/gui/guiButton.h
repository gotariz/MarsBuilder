#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include "general.h"
#include "guiElement.h"
#include "glTexture.h"

class guiButton : public guiElement
{
    public:
        guiButton(int _id = -1) : guiElement(_id,GUI_BUTTON) {}
        virtual ~guiButton(){}

    public:
        glTexture   m_img;
        Rec         r_buttton;

        Colour cIdle    = Colour(0.19f,0.19f,0.19f);
        Colour cHover   = Colour(0.3f,0.3f,0.3f);
        Colour cActive  = Colour(0.f,0.53f,0.8f);

        virtual void draw();
        virtual void freeResources();

        virtual void onEnter();
        virtual void onExit();
        virtual void onMouseDown();
        virtual void onMouseUp();
        virtual void onDragExit();
        virtual void onDragEnter();

};

#endif // GUIBUTTON_H
