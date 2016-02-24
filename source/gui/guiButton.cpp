#include "guiButton.h"

void guiButton::draw()
{
    Colour c;
    if (m_state == IDLE or m_state == SELECTED) {
        c = cIdle;
    } else if (m_state == HOVER) {
        c = cHover;
    } else if (m_state == ACTIVE or TOGGLED) {
        c = cActive;
    }

    Rec temp = Rec(m_actualPosition.x,m_actualPosition.y,m_size.w,m_size.h);
    drawRectangle(temp,c);
    m_img.draw(m_actualPosition.x,m_actualPosition.y);
}

void guiButton::freeResources()
{
    m_img.freeTexture();
}

void guiButton::onEnter()
{
    if (m_state != TOGGLED)
    {
        m_state = HOVER;
    }
}

void guiButton::onExit()
{
    if (m_state != TOGGLED)
    {
        m_state = IDLE;
    }
}

void guiButton::onMouseDown()
{
    if (m_state != TOGGLED)
    {
        m_state = ACTIVE;
    }
}

void guiButton::onDragExit()
{
    if (m_state == ACTIVE) {
        m_state = SELECTED;
    }
}

void guiButton::onDragEnter()
{
    if (m_state == SELECTED) {
        m_state = ACTIVE;
    }
}

void guiButton::onMouseUp()
{
    if (m_isToggle)
    {
        if (m_state == TOGGLED) {
            m_state = HOVER;
        } else {
            m_state = TOGGLED;
        }
    } else {
        m_state = HOVER;
    }
}



