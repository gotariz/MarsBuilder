#include "guiElement.h"

void guiElement::draw() {}
void guiElement::freeResources(){}

int guiElement::getID()
{
    return m_id;
}

bool guiElement::isPointTouching(Point mousePosition)
{
    if (mousePosition.x < m_actualPosition.x) return false;                                             // out of bounds to the left
    else if (mousePosition.x >= globals.rScreen.x + m_actualPosition.x + m_actualSize.w) return false;  // out of bounds to the right

    if (mousePosition.y <= m_actualPosition.y) return false;                                            // out of bound to the bottom
    else if (mousePosition.y > globals.rScreen.y + m_actualPosition.y + m_actualSize.h) return false;   // out of bound to the top

    return true;
}

void guiElement::setAnchor(int v, int h)
{
    v_anchor = v;
    h_anchor = h;
}

void guiElement::onEnter()
{
    m_state = HOVER;
}

void guiElement::onExit()
{
    m_state = IDLE;
}

void guiElement::onMouseDown()
{
    m_state = ACTIVE;
}

void guiElement::onDragExit()
{
    if (m_state == ACTIVE)
    {
        m_state = SELECTED;
    }
}

void guiElement::onDragEnter()
{
    if (m_state == SELECTED)
    {
        m_state = ACTIVE;
    }
}

void guiElement::onMouseUp()
{
    m_state = HOVER;
}






