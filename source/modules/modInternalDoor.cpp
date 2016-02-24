#include "modInternalDoor.h"

void modInternalDoor::setP2(int x, int y)
{
    p2.set(x,y);
    p1 = p2;
}

void modInternalDoor::calculatePositionAndSize()
{
    x = p1.x;
    y = p1.y;
    w = maxSize;
    h = minSize;
}

void modInternalDoor::calibrate()
{
    clearBlocks();

    int dx = x - (maxSize / 2);
    int dy = y;
    int dw = maxSize;
    int dh = minSize;
    if (orientation == VERTICAL)
    {
        dx = x;
        dy = y - (maxSize / 2);
        dw = minSize;
        dh = maxSize;
    }

    Colour colour = C_GREEN;

    BuildingBlock* door = new BuildingBlock(INTERIOR_DOOR);
    door->set(dx,dy,dw,dh);
    door->setColour(colour);
    door->collisionFlag = INTERIOR_DOOR;
    door->collisionMask = ~NONE ^ INTERIOR_WALL ^ INTERIOR; // all except LOW_GRADE_WALLs
    door->containerMask = INTERIOR_WALL;
    door->setColBufferSize(QUARTER_UNIT); // there is not specified restriction on interal walls
    door->setConBufferSize(QUARTER_UNIT);
    door->setOrientation(orientation); // the orientation of this block is the same as the module
    blocks.push_back(door);
}

