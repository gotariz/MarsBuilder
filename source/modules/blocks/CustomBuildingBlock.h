#ifndef CUSTOMBUILDINGBLOCK_H
#define CUSTOMBUILDINGBLOCK_H

#include "BuildingBlock.h"

class CustomBuildingBlock : public BuildingBlock
{
    public:
        CustomBuildingBlock(int blockType) : BuildingBlock(blockType){}
        virtual ~CustomBuildingBlock(){}

        int angle = 0;
    public:

        void setAngle(int a){angle = a;}
        virtual void render();
};

#endif // CUSTOMBUILDINGBLOCK_H
