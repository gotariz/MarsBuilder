#ifndef MODHIGHGRADEDOOR_H
#define MODHIGHGRADEDOOR_H

#include "general.h"
#include "modContained.h"

class modHighGradeDoor : public modContained
{
    public:
        modHighGradeDoor(){
            minSize         = QUARTER_UNIT;
            maxSize         = UNIT;
            incrementSize   = QUARTER_UNIT;

            movable = true;
            resizable = false;

            type = M_HIGH_GRADE_DOOR;
        }
        virtual ~modHighGradeDoor(){}

    public:

        virtual bool isValidPosition(std::vector<Module*> modules);
        virtual void calculatePositionAndSize();
        virtual void setP2(int x, int y);
        virtual void calibrate();
        virtual void rotate(){}
};

#endif // MODHIGHGRADEDOOR_H
