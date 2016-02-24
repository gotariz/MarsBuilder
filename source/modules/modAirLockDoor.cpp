#include "modAirLockDoor.h"

void modAirLockDoor::calculatePositionAndSize()
{
    x = p1.x - (maxSize / 2);
    y = p1.y;
    w = maxSize;
    h = minSize;
}

void modAirLockDoor::setP2(int x, int y)
{
    p2.set(x,y);
    p1 = p2;
}

void modAirLockDoor::calibrate()
{
    clearBlocks();

    if (orientation == VERTICAL)
    {
        x = p1.x;
        y = p1.y - (maxSize / 2);
        w = minSize;
        h = maxSize;
    }

    Colour colour   = C_RED;
    Colour colour2  = C_RED_TRANSPARENT;

    BuildingBlock* door1 = new BuildingBlock(HIGH_GRADE_DOOR);
    door1->set(x,y,w,h);
    door1->setColour(colour);
    door1->collisionFlag = HIGH_GRADE_DOOR;
    door1->collisionMask = ~NONE ^ HIGH_GRADE_WALL; // all except LOW_GRADE_WALLs
    door1->containerMask = HIGH_GRADE_WALL;
    door1->setColBufferSize(UNIT);
    door1->setConBufferSize(20); // special distance just for high grade windows
    door1->setOrientation(orientation); // the orientation of this block is the same as the module
    door1->setName("connectingdoor");
    blocks.push_back(door1);

    BuildingBlock* door2 = new BuildingBlock(HIGH_GRADE_DOOR);
    door2->set(x,y-UNIT,w,h);
    door2->setColour(colour);
    door2->collisionFlag = HIGH_GRADE_DOOR;
    door2->collisionMask = ~NONE ^ HIGH_GRADE_WALL; // all except LOW_GRADE_WALLs
    door2->containerMask = NONE;
    door2->setColBufferSize(UNIT);
    door2->setConBufferSize(20); // special distance just for high grade windows
    door2->setOrientation(orientation); // the orientation of this block is the same as the module
    blocks.push_back(door2);

    // create the left wall
    BuildingBlock* left = new BuildingBlock(HIGH_GRADE_WALL);
    left->setPosition(x-HIGH_GRADE_SIZE,y-UNIT);
    left->setSize(HIGH_GRADE_SIZE,UNIT);
    left->setOrientation(VERTICAL);
    left->collisionFlag = HIGH_GRADE_WALL;
    left->collisionMask = INTERIOR | HIGH_GRADE_WALL | LOW_GRADE_WALL;
    left->setColour(colour2);
    blocks.push_back(left);

    // create the right wall
    BuildingBlock* right = new BuildingBlock(HIGH_GRADE_WALL);
    right->setPosition(x+UNIT,y-UNIT);
    right->setSize(HIGH_GRADE_SIZE,UNIT);
    right->setOrientation(VERTICAL);
    right->collisionFlag = HIGH_GRADE_WALL;
    right->collisionMask = INTERIOR | HIGH_GRADE_WALL | LOW_GRADE_WALL;
    right->setColour(colour2);
    blocks.push_back(right);
}

// Could use some cleaning up
bool modAirLockDoor::isValidPosition(std::vector<Module* > modules)
{
    bool isContained = false;
    bool isColliding = false;

    std::vector<BuildingBlock*> lowest;

    // check all modules
    for (unsigned i = 0; i < modules.size(); ++i)
    {
        // check all blocks in that module
        Module* m = modules.at(i);
        // find all lowest bottom walls
        BuildingBlock* bottom = m->getBlockByName("bottomwall");
        if (bottom != nullptr)
        {
            if (lowest.size() == 0 or bottom->getBox().y == lowest.at(0)->getBox().y) {
                lowest.push_back(bottom);
            } else if (bottom->getBox().y < lowest.at(0)->getBox().y) {
                lowest.clear();
                lowest.push_back(bottom);
            }
        }

        for (unsigned j = 0; j < m->getBlocks()->size(); ++j)
        {
            // check all blocks against the blocks in this module
            BuildingBlock* b2 = m->getBlocks()->at(j);
            for (unsigned k = 0; k < blocks.size(); ++k)
            {
                BuildingBlock* b1 = blocks.at(k);
                if (b1->isColliding(b2)) isColliding = true;
            }

        }
    }

    // check if the door is contained in any of the lowest walls
    BuildingBlock* bottom = getBlockByName("connectingdoor");
    for (unsigned i = 0; i < lowest.size(); ++i)
    {
        if (bottom->isContained(lowest.at(i))) {
        	isContained = true;
        	i = lowest.size(); // no need to check more
        }
    }

    return (isContained and !isColliding);
}
