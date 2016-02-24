#include "modHighGrade.h"


void modHighGrade::calibrate()
{
    // clear any exisiting blocks becasue we are going to remake them
    clearBlocks();

    // don't create the module if it's below the minSize requirement
    if (w < minSize)    return;
    if (h < minSize)    return;

    // create the left wall
    BuildingBlock* interior = new BuildingBlock(INTERIOR);
    interior->set(x,y,w,h);
    interior->collisionFlag = INTERIOR;
    interior->collisionMask = INTERIOR | HIGH_GRADE_WALL | LOW_GRADE_WALL;
    blocks.push_back(interior);

    Colour colour = C_RED_TRANSPARENT;
    // create the bottom wall
    BuildingBlock* bottom = new BuildingBlock(HIGH_GRADE_WALL);
    bottom->setPosition(x+UNIT,y-HIGH_GRADE_SIZE);
    bottom->setSize(w-(UNIT*2),HIGH_GRADE_SIZE);
    bottom->setOrientation(HORIZONTAL);
    bottom->collisionFlag = HIGH_GRADE_WALL;
    bottom->collisionMask = INTERIOR | HIGH_GRADE_WALL | LOW_GRADE_WALL;
    bottom->setColour(colour);
    bottom->setName("bottomwall");
    blocks.push_back(bottom);

    // create the top wall
    BuildingBlock* top = new BuildingBlock(HIGH_GRADE_WALL);
    top->setPosition(x+UNIT,y+h);
    top->setSize(w-(UNIT*2),HIGH_GRADE_SIZE);
    top->setOrientation(HORIZONTAL);
    top->collisionFlag = HIGH_GRADE_WALL;
    top->collisionMask = INTERIOR | HIGH_GRADE_WALL | LOW_GRADE_WALL;
    top->setColour(colour);
    blocks.push_back(top);

    // create the left wall
    BuildingBlock* left = new BuildingBlock(HIGH_GRADE_WALL);
    left->setPosition(x-HIGH_GRADE_SIZE,y+UNIT);
    left->setSize(HIGH_GRADE_SIZE,h-(UNIT*2));
    left->setOrientation(VERTICAL);
    left->collisionFlag = HIGH_GRADE_WALL;
    left->collisionMask = INTERIOR | HIGH_GRADE_WALL | LOW_GRADE_WALL;
    left->setColour(colour);
    blocks.push_back(left);

    // create the right wall
    BuildingBlock* right = new BuildingBlock(HIGH_GRADE_WALL);
    right->setPosition(x+w,y+UNIT);
    right->setSize(HIGH_GRADE_SIZE,h-(UNIT*2));
    right->setOrientation(VERTICAL);
    right->collisionFlag = HIGH_GRADE_WALL;
    right->collisionMask = INTERIOR | HIGH_GRADE_WALL | LOW_GRADE_WALL;
    right->setColour(colour);
    blocks.push_back(right);

    // top right wall corner
    CustomBuildingBlock* tr = new CustomBuildingBlock(HIGH_GRADE_WALL);
    tr->setPosition(x+w-UNIT,y+h-UNIT);
    tr->setSize(UNIT+HIGH_GRADE_SIZE,UNIT+HIGH_GRADE_SIZE);
    tr->collisionFlag = HIGH_GRADE_WALL;
    tr->collisionMask = ~NONE; // add accessories that can be attached to walls
    tr->setColour(colour);
    tr->setAngle(0);
    blocks.push_back(tr);

    // top left wall corner
    CustomBuildingBlock* tl = new CustomBuildingBlock(HIGH_GRADE_WALL);
    tl->setPosition(x-HIGH_GRADE_SIZE,y+h-UNIT);
    tl->setSize(UNIT+HIGH_GRADE_SIZE,UNIT+HIGH_GRADE_SIZE);
    tl->collisionFlag = HIGH_GRADE_WALL;
    tl->collisionMask = ~NONE;
    tl->setColour(colour);
    tl->setAngle(90);
    blocks.push_back(tl);

    // bottom left wall corner
    CustomBuildingBlock* bl = new CustomBuildingBlock(HIGH_GRADE_WALL);
    bl->setPosition(x-HIGH_GRADE_SIZE,y-HIGH_GRADE_SIZE);
    bl->setSize(UNIT+HIGH_GRADE_SIZE,UNIT+HIGH_GRADE_SIZE);
    bl->collisionFlag = HIGH_GRADE_WALL;
    bl->collisionMask = ~NONE;
    bl->setColour(colour);
    bl->setAngle(180);
    blocks.push_back(bl);

    // bottom right wall corner
    CustomBuildingBlock* br = new CustomBuildingBlock(HIGH_GRADE_WALL);
    br->setPosition(x+w-UNIT,y-HIGH_GRADE_SIZE);
    br->setSize(UNIT+HIGH_GRADE_SIZE,UNIT+HIGH_GRADE_SIZE);
    br->collisionFlag = HIGH_GRADE_WALL;
    br->collisionMask = ~NONE; // add accessories that can be attached to walls
    br->setColour(colour);
    br->setAngle(270);
    blocks.push_back(br);
}
