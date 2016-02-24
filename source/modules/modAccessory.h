#ifndef MODACCESSORY_H
#define MODACCESSORY_H

#include "general.h"
#include "modContained.h"
#include "blocks/AccessoryBuildingBlock.h"
#include "gui/Font.h"

class modAccessory : public modContained
{
    public:
        modAccessory(){
            minSize         = QUARTER_UNIT;
            maxSize         = 5 * UNIT;
            incrementSize   = QUARTER_UNIT;

            movable        = true;
            resizable       = true;
        }
        virtual ~modAccessory(){}

    public:
        virtual void calibrate();
        virtual void rotate(){}
};

#endif // MODACCESSORY_H
