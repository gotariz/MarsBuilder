#include "modHighGradeDoor.h"

void modHighGradeDoor::setP2(int x, int y)
{
    p2.set(x,y);
    p1 = p2;
}

void modHighGradeDoor::calculatePositionAndSize()
{
    x = p1.x - (maxSize / 2);
    y = p1.y;
    w = maxSize;
    h = minSize;
}

void modHighGradeDoor::calibrate()
{
    clearBlocks();

    Colour colour = C_RED;

    BuildingBlock* b = new BuildingBlock(HIGH_GRADE_DOOR);
    b->set(x,y,w,h);
    b->setColour(colour);
    b->collisionFlag = HIGH_GRADE_DOOR;
    b->collisionMask = ~NONE ^ HIGH_GRADE_WALL; // all except LOW_GRADE_WALLs
    b->containerMask = HIGH_GRADE_WALL;
    b->setColBufferSize(UNIT);
    b->setConBufferSize(20); // special distance just for high grade windows
    b->setOrientation(HORIZONTAL); // the orientation of this block is the same as the module
    blocks.push_back(b);
}

// could use some cleaning up
bool modHighGradeDoor::isValidPosition(std::vector<Module* > modules)
{
    bool isContained = false;
    bool isColliding = false;

    std::vector<BuildingBlock*> lowest;

    // check all modules
    for (unsigned i = 0; i < modules.size(); ++i)
    {
        // check all blocks in that module
        Module* m = modules.at(i);
        // find all high grade walls on the bottom edge
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
            //high grade door has 1 and only 1 building block
            if (blocks.at(0)->isColliding(b2)) isColliding = true;
        }
    }

    // check if the door is contained in any of the lowest walls
    BuildingBlock* bottom = blocks.at(0);
    for (unsigned i = 0; i < lowest.size(); ++i)
    {
        if (bottom->isContained(lowest.at(i))) {
        	isContained = true;
        	i = lowest.size();
        }
    }

    return (isContained and !isColliding);
}

