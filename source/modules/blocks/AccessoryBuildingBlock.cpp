#include "AccessoryBuildingBlock.h"

void AccessoryBuildingBlock::render()
{
    glColor3f(C_BLACK.r,C_BLACK.g,C_BLACK.b);

    glBegin(GL_LINE_LOOP);
        glVertex2i(box.x,box.y);
        glVertex2i(box.x+box.w,box.y);
        glVertex2i(box.x+box.w,box.y+box.h);
        glVertex2i(box.x,box.y+box.h);
    glEnd();

    // should probably check for illegal characters
    if (font != nullptr and name != "")
    {
        font->setColour(C_BLACK);
        int x = box.x + (box.w/2) - (font->getStringWidth(name)/2); // horizontal center
        int y = box.y + (box.h/2) - (font->getFontHeight()/2); // vertical center
        font->printString(x,y,name);
    }
}

