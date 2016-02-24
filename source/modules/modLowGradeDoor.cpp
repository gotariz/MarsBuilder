#include "modLowGradeDoor.h"

void modLowGradeDoor::setP2(int x, int y)
{
    p2.set(x,y);
    p1 = p2;
}

void modLowGradeDoor::calculatePositionAndSize()
{
    x = p1.x;// - (maxSize / 2);
    y = p1.y;// - (minSize / 2);
    w = maxSize;
    h = minSize;
}

void modLowGradeDoor::calibrate()
{
    clearBlocks();

    int wx = x - (maxSize / 2);
    int wy = y - (minSize / 2);
    int ww = maxSize;
    int wh = minSize;
    if (orientation == VERTICAL)
    {
        wx = x - (minSize / 2);
        wy = y - (maxSize / 2);
        ww = minSize;
        wh = maxSize;
    }

    Colour colour = C_RED;

    BuildingBlock* b = new BuildingBlock(LOW_GRADE_DOOR);
    b->set(wx,wy,ww,wh);
    b->setColour(colour);
    b->collisionFlag = LOW_GRADE_DOOR;
    b->collisionMask = LOW_GRADE_DOOR | LOW_GRADE_WINDOW; // all except LOW_GRADE_WALLs
    b->containerMask = LOW_GRADE_WALL;
    b->setColBufferSize(UNIT + HALF_UNIT);
    b->setConBufferSize(HALF_UNIT);
    b->setOrientation(orientation); // the orientation of this block is the same as the module
    blocks.push_back(b);
}


