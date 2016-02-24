#include "modConnectingDoor.h"

void modConnectingDoor::setP2(int x, int y)
{
    p2.set(x,y);
    p1 = p2;
}

// there are 2 doors that need to be contained not just one
bool modConnectingDoor::isValidPosition(std::vector<Module* > modules)
{
    int isContained = 0; // keeps track of how many objects have been contained
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
                if (b1->isContained(b2)) ++isContained; // increment the number of objects that have been contained
            }

        }
    }

    // only return true if both objects have been contained
    return (isContained == 2 and !isColliding);
}

void modConnectingDoor::calculatePositionAndSize()
{
    x = p1.x;// - (maxSize / 2);
    y = p1.y;
    w = maxSize;
    h = minSize;
}


void modConnectingDoor::calibrate()
{
    clearBlocks();

    int dx = x - (maxSize / 2);
    int dy = y;
    int dw = maxSize;
    int dh = minSize;
    int dx2 = dx;
    int dy2 = y-HIGH_GRADE_SIZE;

    if (orientation == VERTICAL)
    {
        dx = x;
        dy = y - (maxSize / 2);
        dw = minSize;
        dh = maxSize;
        dx2 = x-HIGH_GRADE_SIZE;
        dy2 = dy;
    }

    Colour colour = C_RED;

    BuildingBlock* door1 = new BuildingBlock(HIGH_GRADE_DOOR);
    door1->set(dx,dy,dw,dh);
    door1->setColour(colour);
    door1->collisionFlag = HIGH_GRADE_DOOR;
    door1->collisionMask = ~NONE ^ HIGH_GRADE_WALL; // all except LOW_GRADE_WALLs
    door1->containerMask = HIGH_GRADE_WALL;
    door1->setColBufferSize(UNIT);
    door1->setConBufferSize(20); // special distance just for high grade windows
    door1->setOrientation(orientation); // the orientation of this block is the same as the module
    blocks.push_back(door1);

    BuildingBlock* door2 = new BuildingBlock(HIGH_GRADE_DOOR);
    door2->set(dx2,dy2,dw,dh);
    door2->setColour(colour);
    door2->collisionFlag = HIGH_GRADE_DOOR;
    door2->collisionMask = ~NONE ^ HIGH_GRADE_WALL; // all except LOW_GRADE_WALLs
    door2->containerMask = HIGH_GRADE_WALL;
    door2->setColBufferSize(UNIT);
    door2->setConBufferSize(20); // special distance just for high grade windows
    door2->setOrientation(orientation); // the orientation of this block is the same as the module
    blocks.push_back(door2);
}

