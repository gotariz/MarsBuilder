#include "Module.h"

void Module::setPosition(Point p)
{
    setPosition(p.x,p.y);
}

void Module::setPosition(int newx, int newy)
{
    x = newx;
    y = newy;
}

void Module::setP1(Point p)
{
    setP1(p.x,p.y);
}

void Module::setP2(Point p)
{
    setP2(p.x,p.y);
}

void Module::setP1(int x, int y)
{
    p1.set(x,y);
}

void Module::setP2(int x, int y)
{
    // calculate the size of the selection (can be negative width and height)
    w = x - p1.x;
    h = y - p1.y;

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

void Module::setSize(Point p)
{
    setSize(p.x,p.y);
}

void Module::setSize(int neww, int newh)
{
    w = neww;
    h = newh;
}

void Module::render()
{
    for (unsigned i = 0; i < blocks.size(); ++i)
    {
        blocks.at(i)->render();
    }
}

void Module::clearBlocks()
{
    for (unsigned i = 0; i < blocks.size(); ++i)
    {
        delete blocks.at(i);
        blocks.at(i) = nullptr;
    }
    blocks.clear();
}

void Module::calculatePositionAndSize()
{
    // the anchor point of the module
    x = std::min(p1.x,p2.x);
    y = std::min(p1.y,p2.y);

    // calculate to top right corner
    Point topRight;
    topRight.x = std::max(p1.x,p2.x);
    topRight.y = std::max(p1.y,p2.y);

    // calculate the positive width and height
    w = topRight.x - x;
    h = topRight.y - y;
}

bool Module::isValidPosition(std::vector<Module* > modules)
{
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
            }
        }
    }

    return (!isColliding);//isContained and
}

void Module::rotate()
{
    if (orientation == VERTICAL)    orientation = HORIZONTAL;
    else                            orientation = VERTICAL;

    calibrate();
}

// returns the first block with a matching name
BuildingBlock* Module::getBlockByName(std::string name)
{
    for (unsigned i = 0; i < blocks.size(); ++i)
    {
        if (name == blocks.at(i)->getName()) return blocks.at(i);
    }

    return nullptr;
}

bool Module::isTouching(Point p)
{
    for (unsigned i = 0; i < blocks.size(); ++i)
    {
        if ( utils::isContained(p,blocks.at(i)->getBox() ) ) return true;
    }

    return false;
}

void Module::freeResources()
{
    clearBlocks();
}
