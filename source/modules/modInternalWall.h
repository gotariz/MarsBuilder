#ifndef MODINTERNALWALL_H
#define MODINTERNALWALL_H

#include "general.h"
#include "modContained.h"

class modInternalWall : public modContained
{
    public:
        modInternalWall(){
            minSize         = QUARTER_UNIT;
            maxSize         = 15 * UNIT;
            incrementSize   = QUARTER_UNIT;

            movable = false;
            resizable = false;

            type = M_INTERNAL_WALL;
        }
        virtual ~modInternalWall(){}

    public:

        virtual void setP2(int x, int y);
        virtual void calibrate();
        virtual void rotate(){}
};

#endif // MODINTERNALWALL_H
