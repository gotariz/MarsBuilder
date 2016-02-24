#include "modInternalWall.h"

void modInternalWall::setP2(int x, int y)
{
    p2.x = x;
    p2.y = y;

    // calculate the size of the selection (can be negative width and height)
    w = x - p1.x;
    h = y - p1.y;

    // get the absolute width and height
    int aw = w;
    int ah = h;
    if (aw < 0) aw *= -1;
    if (ah < 0) ah *= -1;

    // snap to the closest
    if (aw < ah) {
        if (x < p1.x)       p2.x = p1.x - HIGH_GRADE_SIZE;  // the window is the the left of p1
        else                p2.x = p1.x + HIGH_GRADE_SIZE;  // the window is to the right of p1
        orientation = VERTICAL;
    } else {
        if (y < p1.y)       p2.y = p1.y - HIGH_GRADE_SIZE; // the window is to the bottom of p1
        else                p2.y = p1.y + HIGH_GRADE_SIZE; // the window is to the top of p1
        orientation = HORIZONTAL;
    }

    w = p2.x - p1.x;
    h = p2.y - p1.y;

    // restrict to min size requirements
    if (w > -minSize and w < minSize)   w = roundNearest(w,minSize);
    if (h > -minSize and h < minSize)   h = roundNearest(h,minSize);

    // restrict size to increments
    w = roundNearest(w,incrementSize);
    h = roundNearest(h,incrementSize);

    // don't allow larger than maxSize
    w = std::min(w,maxSize);    // max to the right
    w = std::max(w,-maxSize);   // max to the left
    h = std::min(h,maxSize);    // max to the top
    h = std::max(h,-maxSize);   // max to the bottom

    // the new p2 based on the restrictions
    p2.x = p1.x + w;
    p2.y = p1.y + h;
}

void modInternalWall::calibrate()
{
    clearBlocks();

    // don't create the module if it's below the minSize requirement
    if (w < minSize)    return;
    if (h < minSize)    return;

    Colour colour = C_GREY;

    // create the wall
    BuildingBlock* wall = new BuildingBlock(INTERIOR_WALL);
    wall->setPosition(x,y);
    wall->setSize(w,h);
    wall->collisionFlag = INTERIOR_WALL;
    wall->collisionMask = ~NONE ^ INTERIOR ^ INTERIOR_DOOR;
    wall->containerMask = INTERIOR;
    wall->setColour(colour);
    wall->setOrientation(orientation);
    blocks.push_back(wall);
}
