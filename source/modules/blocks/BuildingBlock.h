#ifndef BUILDINGBLOCK_H
#define BUILDINGBLOCK_H

#include "general.h"

class BuildingBlock
{
    public:
        BuildingBlock(int blockType) : type(blockType){}
        virtual ~BuildingBlock(){}

    protected:
        int type = 0;
        int orientation = HORIZONTAL;
        int colBufferSize = 0;
        int conBufferSize = 0;
        Colour c;

        Rec box;
        Rec colBuffer;
        Rec conBuffer;
        std::string name = "";

    public:
        int collisionFlag = NONE;  // the type of collision object this is
        int collisionMask = NONE;  // the types of collision objects it can collide with
        int containerMask = NONE;  // the types of collision objects it can collide with

        void set(int x, int y, int w, int h);
        void setPosition(int x, int y);
        void setSize(int w, int h);
        void setColBufferSize(int bSize);
        void setConBufferSize(int bSize);
        void setOrientation(int newOrientation);
        int  getOrientation();
        int  getType() {return type;}
        void setColour(Colour colour){c = colour;}

        bool isColliding(const BuildingBlock* b);
        bool isContained(const BuildingBlock* b);

        std::string getName(){return name;}
        void setName(std::string newName){name = newName;}

        virtual void render();

        Rec getBox();
        Rec getColBuffer();
        Rec getConBuffer();
};

#endif // BUILDINGBLOCK_H
