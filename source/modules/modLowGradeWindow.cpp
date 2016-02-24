#include "modLowGradeWindow.h"

void modLowGradeWindow::setP2(int x, int y)
{
    p2.set(x,y);
    p1 = p2;
}

void modLowGradeWindow::calculatePositionAndSize()
{
    x = p1.x;
    y = p1.y;
    w = maxSize;
    h = minSize;
}

void modLowGradeWindow::calibrate()
{
    clearBlocks();
    int dx = x - (maxSize / 2);
    int dy = y - (minSize / 2);
    int dw = maxSize;
    int dh = minSize;

    if (orientation == VERTICAL)
    {
        dx = x - (minSize / 2);
        dy = y - (maxSize / 2);
        dw = minSize;
        dh = maxSize;
    } else {

    }

    Colour colour = C_BLUE; // this is probably better being a member variable

    BuildingBlock* b = new BuildingBlock(LOW_GRADE_WINDOW);
    b->set(dx,dy,dw,dh);
    b->setColour(colour);
    b->collisionFlag = LOW_GRADE_WINDOW;
    b->collisionMask = ~NONE ^ LOW_GRADE_WALL; // all except LOW_GRADE_WALLs
    b->containerMask = LOW_GRADE_WALL;
    b->setColBufferSize(UNIT + HALF_UNIT);
    b->setConBufferSize(HALF_UNIT);
    b->setOrientation(orientation); // the orientation of this block is the same as the module
    blocks.push_back(b);
}

