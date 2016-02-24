#include "modLowGrade.h"

void modLowGrade::calibrate()
{
    // clear any exisiting blocks becasue we are going to remake them
    clearBlocks();

    // don't create the module if it's below the minSize requirement
    if (w < minSize)    return;
    if (h < minSize)    return;

    // create the interior
    BuildingBlock* interior = new BuildingBlock(INTERIOR);
    interior->set(x,y,w,h);
    interior->collisionFlag = INTERIOR;
    interior->collisionMask = INTERIOR | HIGH_GRADE_WALL | LOW_GRADE_WALL;
    blocks.push_back(interior);

    // colour for all the wall blocks
    Colour colour = C_RED_TRANSPARENT;

    // create the bottom wall
    BuildingBlock* bottom = new BuildingBlock(LOW_GRADE_WALL);
    bottom->setPosition(x,y-LOW_GRADE_SIZE);
    bottom->setSize(w,LOW_GRADE_SIZE);
    bottom->setOrientation(HORIZONTAL);
    bottom->collisionFlag = LOW_GRADE_WALL;
    bottom->collisionMask = INTERIOR | HIGH_GRADE_WALL | LOW_GRADE_WALL;
    bottom->setColour(colour);
    blocks.push_back(bottom);

    // create the top wall
    BuildingBlock* top = new BuildingBlock(LOW_GRADE_WALL);
    top->setPosition(x,y+h);
    top->setSize(w,LOW_GRADE_SIZE);
    top->setOrientation(HORIZONTAL);
    top->collisionFlag = LOW_GRADE_WALL;
    top->collisionMask = INTERIOR | HIGH_GRADE_WALL | LOW_GRADE_WALL;
    top->setColour(colour);
    blocks.push_back(top);

    // create the left wall
    BuildingBlock* left = new BuildingBlock(LOW_GRADE_WALL);
    left->setPosition(x-LOW_GRADE_SIZE,y);
    left->setSize(LOW_GRADE_SIZE,h);
    left->setOrientation(VERTICAL);
    left->collisionFlag = LOW_GRADE_WALL;
    left->collisionMask = INTERIOR | HIGH_GRADE_WALL | LOW_GRADE_WALL;
    left->setColour(colour);
    blocks.push_back(left);

    // create the right wall
    BuildingBlock* right = new BuildingBlock(LOW_GRADE_WALL);
    right->setPosition(x+w,y);
    right->setSize(LOW_GRADE_SIZE,h);
    right->setOrientation(VERTICAL);
    right->collisionFlag = LOW_GRADE_WALL;
    right->collisionMask = INTERIOR | HIGH_GRADE_WALL | LOW_GRADE_WALL;
    right->setColour(colour);
    blocks.push_back(right);

    // create corner top left
    BuildingBlock* tl = new BuildingBlock(LOW_GRADE_WALL);
    tl->setPosition(x-LOW_GRADE_SIZE,y+h);
    tl->setSize(LOW_GRADE_SIZE,LOW_GRADE_SIZE);
    tl->collisionFlag = LOW_GRADE_WALL;
    tl->collisionMask = ~NONE;
    tl->setColour(colour);
    blocks.push_back(tl);

    // create corner top right
    BuildingBlock* tr = new BuildingBlock(LOW_GRADE_WALL);
    tr->setPosition(x+w,y+h);
    tr->setSize(LOW_GRADE_SIZE,LOW_GRADE_SIZE);
    tr->collisionFlag = LOW_GRADE_WALL;
    tr->collisionMask = ~NONE;
    tr->setColour(colour);
    blocks.push_back(tr);

    // create corner bottom left
    BuildingBlock* bl = new BuildingBlock(LOW_GRADE_WALL);
    bl->setPosition(x-LOW_GRADE_SIZE,y-LOW_GRADE_SIZE);
    bl->setSize(LOW_GRADE_SIZE,LOW_GRADE_SIZE);
    bl->collisionFlag = LOW_GRADE_WALL;
    bl->collisionMask = ~NONE;
    bl->setColour(colour);
    blocks.push_back(bl);

    // create corner bottom left
    BuildingBlock* br = new BuildingBlock(LOW_GRADE_WALL);
    br->setPosition(x+w,y-LOW_GRADE_SIZE);
    br->setSize(LOW_GRADE_SIZE,LOW_GRADE_SIZE);
    br->collisionFlag = LOW_GRADE_WALL;
    br->collisionMask = ~NONE;
    br->setColour(colour);
    blocks.push_back(br);
}

