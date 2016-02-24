#ifndef MODINTERNALDOOR_H
#define MODINTERNALDOOR_H

#include "general.h"
#include "modContained.h"

class modInternalDoor : public modContained
{
    public:
        modInternalDoor(){
            minSize         = QUARTER_UNIT;
            maxSize         = UNIT;
            incrementSize   = QUARTER_UNIT;

            movable = true;
            resizable = false;

            type = M_INTERNAL_DOOR;
        }
        virtual ~modInternalDoor(){}

    public:

        virtual void calculatePositionAndSize();
        virtual void setP2(int x, int y);
        virtual void calibrate();
};

#endif // MODINTERNALDOOR_H
