#ifndef MODHIGHGRADE_H
#define MODHIGHGRADE_H

#include "general.h"
#include "Module.h"
#include "blocks/BuildingBlock.h"
#include "blocks/CustomBuildingBlock.h"

class modHighGrade : public Module
{
    public:
        modHighGrade(){
            minSize         = 2 * UNIT;
            maxSize         = 15 * UNIT;
            incrementSize   = UNIT;

            // uncomment this to have movable and resizable modules
            //movable = true;
            //resizable = true;

            type = M_HIGH_GRADE;
        }
        virtual ~modHighGrade(){}

    public:
        virtual void calibrate();
        virtual void rotate(){}
};

#endif // MODHIGHGRADE_H
