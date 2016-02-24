#ifndef MODAIRLOCKDOOR_H
#define MODAIRLOCKDOOR_H

#include "general.h"
#include "modContained.h"

class modAirLockDoor : public modContained
{
    public:
        modAirLockDoor(){
            minSize         = QUARTER_UNIT;
            maxSize         = UNIT;
            incrementSize   = QUARTER_UNIT;

            movable = true;
            resizable = false;

            type = M_HIGH_GRADE_AIR_LOCK_DOOR;
        }
        virtual ~modAirLockDoor(){}

    public:

        virtual bool isValidPosition(std::vector<Module*> modules);
        virtual void calculatePositionAndSize();
        virtual void setP2(int x, int y);
        virtual void calibrate();
        virtual void rotate(){}
};

#endif // MODAIRLOCKDOOR_H
