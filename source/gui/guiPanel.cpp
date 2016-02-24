#include "guiPanel.h"

void guiPanel::draw() {
    glColor3f(m_colour.r,m_colour.g,m_colour.b);
    glBegin(GL_POLYGON);
        glVertex2i(m_actualPosition.x,m_actualPosition.y);
        glVertex2i(m_actualPosition.x + m_actualSize.w,m_actualPosition.y);
        glVertex2i(m_actualPosition.x + m_actualSize.w,m_actualPosition.y + m_actualSize.h);
        glVertex2i(m_actualPosition.x,m_actualPosition.y + m_actualSize.h);
    glEnd();
}

