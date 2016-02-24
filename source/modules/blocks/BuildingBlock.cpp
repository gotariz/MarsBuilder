#include "BuildingBlock.h"

void BuildingBlock::set(int x, int y, int w, int h)
{
    box.set(x,y,w,h);
    if (orientation == VERTICAL) {
        colBuffer.set(x,y-colBufferSize,w,h+(colBufferSize*2));
        conBuffer.set(x,y-conBufferSize,w,h+(conBufferSize*2));
    } else {
        colBuffer.set(x-colBufferSize,y,w+(colBufferSize*2),h);
        conBuffer.set(x-conBufferSize,y,w+(conBufferSize*2),h);
    }
}

void BuildingBlock::setPosition(int x, int y)
{
    box.translate(x-box.x,y-box.y);
    colBuffer.translate(x-colBuffer.x,y-colBuffer.y);
    conBuffer.translate(x-conBuffer.x,y-conBuffer.y);
}

void BuildingBlock::setSize(int w, int h)
{
    box.setSize(w,h);
    if (orientation == VERTICAL) {
        colBuffer.setSize(w,h+(colBufferSize*2));
        conBuffer.setSize(w,h+(conBufferSize*2));
    } else {
        colBuffer.setSize(w+(colBufferSize*2),h);
        conBuffer.setSize(w+(conBufferSize*2),h);
    }
}
void BuildingBlock::setColBufferSize(int bSize)
{
    colBufferSize = bSize;
    set(box.x,box.y,box.w,box.h);
}

void BuildingBlock::setConBufferSize(int bSize)
{
    conBufferSize = bSize;
    set(box.x,box.y,box.w,box.h);
}


Rec BuildingBlock::getBox()
{
    return box;
}

Rec BuildingBlock::getColBuffer()
{
    return colBuffer;
}

Rec BuildingBlock::getConBuffer()
{
    return conBuffer;
}

void BuildingBlock::setOrientation(int newOrientation)
{
    orientation = newOrientation;
    set(box.x,box.y,box.w,box.h);
}

int BuildingBlock::getOrientation()
{
    return orientation;
}

bool BuildingBlock::isColliding(const BuildingBlock* b)
{
    if (collisionMask & b->collisionFlag)
    {
        return utils::isOverlapping(colBuffer,b->box);
    }

    return false;
}

bool BuildingBlock::isContained(const BuildingBlock* b)
{
    if (containerMask & b->collisionFlag)
    {
        return utils::isContained(conBuffer,b->box);
    }

    return false;
}

void BuildingBlock::render()
{
    // do not render these types
    if (type == INTERIOR) return;

    drawRectangle(box,c);
    //drawRectangle(colBuffer,C_GREEN_TRANSPARENT);
}




