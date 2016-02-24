#ifndef MODLOWGRADEDOOR_H
#define MODLOWGRADEDOOR_H

#include "general.h"
#include "modContained.h"

class modLowGradeDoor : public modContained
{
    public:
        modLowGradeDoor(){
            minSize         = HALF_UNIT;
            maxSize         = UNIT;
            incrementSize   = 0;

            movable = true;
            resizable = false;

            type = M_LOW_GRADE_DOOR;
        }
        virtual ~modLowGradeDoor(){}

    public:

        virtual void calculatePositionAndSize();
        virtual void setP2(int x, int y);
        virtual void calibrate();
};

#endif // MODLOWGRADEDOOR_H
