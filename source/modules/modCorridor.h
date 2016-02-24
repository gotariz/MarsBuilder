#ifndef MODCORRIDOR_H
#define MODCORRIDOR_H

#include "general.h"
#include "modContained.h"

class modCorridor : public modContained
{
    public:
        modCorridor(){
            minSize         = UNIT;
            maxSize         = 6 * UNIT;
            incrementSize   = HALF_UNIT;

            movable = true;
            resizable = true;

            type = M_CORRIDOR;
        }
        virtual ~modCorridor(){}

    public:

        virtual bool isValid(){return w >= minSize or h >= minSize;}
        virtual bool isValidPosition(std::vector<Module*> modules);
        virtual void setP2(int x, int y);
        virtual void calibrate();
        virtual void rotate(){}
};

#endif // MODCORRIDOR_H
