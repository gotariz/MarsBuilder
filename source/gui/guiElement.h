#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include "general.h"
#include "glTexture.h"

class guiManager;

class guiElement
{
    friend class guiManager;
    public:
        guiElement(int id = -1, int type = GUI_UNKNOWN) : m_id(id), m_type(type){}
        virtual ~guiElement(){}

    protected:
        int m_id    = -1;
        int m_type  = GUI_UNKNOWN;

        // used by guiManager
        Point         m_actualPosition;     // actual pixel position where the element that will be drawn
        Dimension     m_actualSize;         // actual pixel size of the element that will be drawn

    public:
        std::string text        = "";
        int         m_state     = IDLE;
        int         m_group     = 0;
        bool        m_isToggle  = false;

        Colour      m_colour;   // the colour to draw the element
        Point       m_position; // context sensitive description of where the element will be drawn
        Dimension   m_size;     // context sensitive description of the element that will be drawn

        int         v_anchor = BOTTOM;// indicates what side of the screen to draw from
        int         h_anchor = LEFT;
        RelativeSize m_relative_w;  // indicates whether the size is a ratio of the screen size
        RelativeSize m_relative_h;

    public:
        int     getID();
        void    setAnchor(int v, int h);
        bool    isPointTouching(Point _mousePosition);

        virtual void draw();
        virtual void freeResources();

        // EVENTS
        virtual void onEnter();
        virtual void onExit();
        virtual void onMouseDown();
        virtual void onMouseUp();
        virtual void onDragExit();
        virtual void onDragEnter();
};

#endif // GUIELEMENT_H
