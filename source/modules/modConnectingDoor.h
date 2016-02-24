#ifndef MODCONNECTINGDOOR_H
#define MODCONNECTINGDOOR_H

#include "general.h"
#include "modContained.h"

// just like a normal high grade door but joined
class modConnectingDoor : public modContained
{
    public:
        modConnectingDoor(){
            minSize         = QUARTER_UNIT;
            maxSize         = UNIT;
            incrementSize   = QUARTER_UNIT;

            movable = true;
            resizable = false;

            type = M_HIGH_GRADE_CONNTECTING_DOOR;
        }
        virtual ~modConnectingDoor(){}

    public:
        virtual void calculatePositionAndSize();
        virtual void setP2(int x, int y);
        virtual void calibrate();
        virtual bool isValidPosition(std::vector<Module*> modules);
};

#endif // MODCONNECTINGDOOR_H
