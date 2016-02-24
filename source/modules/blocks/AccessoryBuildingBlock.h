#ifndef ACCESSORYBUILDINGBLOCK_H
#define ACCESSORYBUILDINGBLOCK_H

#include "BuildingBlock.h"
#include "gui/Font.h"

class AccessoryBuildingBlock : public BuildingBlock
{
    public:
        AccessoryBuildingBlock(int blockType) : BuildingBlock(blockType){}
        virtual ~AccessoryBuildingBlock(){}

    public:
        Font* font = nullptr; // this class is not responsible for this fonts memory so don't try to manage it
        virtual void render();
};

#endif // ACCESSORYBUILDINGBLOCK_H
