#ifndef MODLOWGRADE_H
#define MODLOWGRADE_H

#include "Module.h"

class modLowGrade : public Module
{
    public:
        modLowGrade(){
            minSize         = UNIT;
            maxSize         = 5 * UNIT;
            incrementSize   = HALF_UNIT;

            // uncomment this to have movable and resizable modules
            //movable = true;
            //resizable = true;

            type = M_LOW_GRADE;
        }
        virtual ~modLowGrade(){}

    public:
        virtual void calibrate();
        virtual void rotate(){}

};

#endif // MODLOWGRADE_H
