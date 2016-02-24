#ifndef MODULE_H
#define MODULE_H

#include "general.h"
#include "blocks/BuildingBlock.h"

class Module
{
    public:
        Module(){}
        virtual ~Module(){}

        void freeResources();
    protected:
        int type = -1;

        Point       p1;
        Point       p2;
        int x = 0;
        int y = 0;
        int w = 0;
        int h = 0;
        int minSize         = QUARTER_UNIT;
        int maxSize         = UNIT * UNIT;
        int incrementSize   = QUARTER_UNIT;

        int orientation = HORIZONTAL;

        std::vector<BuildingBlock*>  blocks;
        std::string name = "";

    public:
        int getModuleType(){return type;}
        void setModuleType(int moduleType){type = moduleType;} // this is only for accessories since they all use the one class

        Point getSize(){return Point(w,h);}
        Point getPosition(){return Point(x,y);}
        int getOrientation() {return orientation;}
        void setOrientation(int newO) {orientation = newO;}

        void setPosition(Point p);
        void setPosition(int x, int y);

        Point getP1(){return p1;}
        Point getP2(){return p2;}
        void setP1(Point p);
        void setP2(Point p);
        virtual void setP1(int x, int y);
        virtual void setP2(int x, int y);

        void setSize(Point p);
        void setSize(int w, int h);

        virtual void calculatePositionAndSize();
        virtual void calibrate(){}
        virtual void render();
        virtual bool isValid(){return w >= minSize and h >= minSize;}
        virtual bool isValidPosition(std::vector<Module*> modules);

        void clearBlocks();
        virtual void rotate();

        void setName(std::string newName){name = newName;}

        BuildingBlock* getBlockByName(std::string name);
        std::vector<BuildingBlock*>* getBlocks(){return &blocks;}

        bool isTouching(Point p);
        bool movable = false;
        bool resizable = false;
};

#endif // MODULE_H
