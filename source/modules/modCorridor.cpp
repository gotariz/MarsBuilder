#include "modCorridor.h"

bool modCorridor::isValidPosition(std::vector<Module* > modules)
{
    int isContained = 0;
    bool isColliding = false;

    // check all modules
    for (unsigned i = 0; i < modules.size(); ++i)
    {
        // check all blocks in that module
        Module* m = modules.at(i);
        for (unsigned j = 0; j < m->getBlocks()->size(); ++j)
        {
            // check all blocks against the blocks in this module
            BuildingBlock* b2 = m->getBlocks()->at(j);
            for (unsigned k = 0; k < blocks.size(); ++k)
            {
                BuildingBlock* b1 = blocks.at(k);
                if (b1->isColliding(b2)) isColliding = true;
                if (b1->isContained(b2)) ++isContained;
            }

        }
    }

    return (isContained == 2 and !isColliding);
}

void modCorridor::setP2(int x, int y)
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
        //if (x < p1.x)       p2.x = p1.x - LOW_GRADE_SIZE;  // the window is the the left of p1
        //else                p2.x = p1.x + LOW_GRADE_SIZE;  // the window is to the right of p1

        p2.x = p1.x;
        orientation = VERTICAL;
    } else {
        //if (y < p1.y)       p2.y = p1.y - LOW_GRADE_SIZE; // the window is to the bottom of p1
        //else                p2.y = p1.y + LOW_GRADE_SIZE; // the window is to the top of p1

        p2.y = p1.y;
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

void modCorridor::calibrate()
{
    clearBlocks();

    // don't create the module if it's below the minSize requirement
    if (w < minSize and h < minSize)    return;

    Colour colour = C_RED;
    Colour colour2 = C_RED_TRANSPARENT;

    int doorOrientation = orientation == HORIZONTAL ? VERTICAL : HORIZONTAL;

    // starting high grade door
    BuildingBlock* door1 = new BuildingBlock(HIGH_GRADE_DOOR);
    if (orientation == HORIZONTAL)  door1->set(x-HIGH_GRADE_SIZE,y-HALF_UNIT,QUARTER_UNIT,UNIT);
    else                            door1->set(x-HALF_UNIT,y-HIGH_GRADE_SIZE,UNIT,QUARTER_UNIT);
    door1->setColour(colour);
    door1->collisionFlag = HIGH_GRADE_DOOR;
    door1->collisionMask = ~NONE ^ HIGH_GRADE_WALL; // all except HIGH_GRADE_WALLs
    door1->containerMask = HIGH_GRADE_WALL;
    door1->setColBufferSize(UNIT);
    door1->setConBufferSize(20); // special distance just for high grade windows
    door1->setOrientation(doorOrientation); // the orientation of this block is the same as the module
    blocks.push_back(door1);

    BuildingBlock* door2 = new BuildingBlock(HIGH_GRADE_DOOR);
    if (orientation == HORIZONTAL)  door2->set(x+w,y-HALF_UNIT,QUARTER_UNIT,UNIT);
    else                            door2->set(x-HALF_UNIT,y+h,UNIT,QUARTER_UNIT);
    door2->setColour(colour);
    door2->collisionFlag = HIGH_GRADE_DOOR;
    door2->collisionMask = ~NONE ^ HIGH_GRADE_WALL; // all except LOW_GRADE_WALLs
    door2->containerMask = HIGH_GRADE_WALL;
    door2->setColBufferSize(UNIT);
    door2->setConBufferSize(20); // special distance just for high grade windows
    door2->setOrientation(doorOrientation); // the orientation of this block is the same as the module
    blocks.push_back(door2);

    // create the bottom wall
    BuildingBlock* wall1 = new BuildingBlock(LOW_GRADE_WALL);
    if (orientation == HORIZONTAL)  wall1->set(x,y-UNIT,w,LOW_GRADE_SIZE);
    else                            wall1->set(x-UNIT,y,LOW_GRADE_SIZE,h);
    wall1->setOrientation(orientation);
    wall1->collisionFlag = LOW_GRADE_WALL;
    wall1->collisionMask = INTERIOR | HIGH_GRADE_WALL | LOW_GRADE_WALL;
    wall1->setColour(colour2);
    blocks.push_back(wall1);

    // create the bottom wall
    BuildingBlock* wall2 = new BuildingBlock(LOW_GRADE_WALL);
    if (orientation == HORIZONTAL)  wall2->set(x,y+LOW_GRADE_SIZE,w,LOW_GRADE_SIZE);
    else                            wall2->set(x+LOW_GRADE_SIZE,y,LOW_GRADE_SIZE,h);
    wall2->setOrientation(orientation);
    wall2->collisionFlag = LOW_GRADE_WALL;
    wall2->collisionMask = INTERIOR | HIGH_GRADE_WALL | LOW_GRADE_WALL;
    wall2->setColour(colour2);
    blocks.push_back(wall2);
}
