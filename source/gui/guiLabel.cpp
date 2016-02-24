#include "guiLabel.h"


void guiLabel::draw()
{
    if (font == nullptr) return;

    font->setColour(C_WHITE);
    font->printString(m_actualPosition.x,m_actualPosition.y,text);
}
