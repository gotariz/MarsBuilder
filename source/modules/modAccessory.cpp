#include "modAccessory.h"

void modAccessory::calibrate()
{
    // clear any exisiting blocks becasue we are going to remake them
    clearBlocks();

    // don't create the module if it's below the minSize requirement
    if (w < minSize)    return;
    if (h < minSize)    return;

    AccessoryBuildingBlock* accessory = new AccessoryBuildingBlock(ACCESSORY);
    accessory->set(x,y,w,h);
    accessory->collisionFlag = ACCESSORY;
    accessory->collisionMask = ~NONE ^ INTERIOR;
    accessory->containerMask = INTERIOR;
    accessory->font = globals.fontNormal;
    accessory->setName(name);
    blocks.push_back(accessory);
}

