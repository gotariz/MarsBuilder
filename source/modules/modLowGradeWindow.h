#ifndef MODLOWGRADEWINDOW_H
#define MODLOWGRADEWINDOW_H

#include "general.h"
#include "modContained.h"


class modLowGradeWindow : public modContained
{
    public:
        modLowGradeWindow(){
            minSize         = HALF_UNIT;
            maxSize         = HALF_UNIT;
            incrementSize   = 0;

            movable = true;
            resizable = false;

            type = M_LOW_GRADE_WINDOW;
        }
        virtual ~modLowGradeWindow(){}

    public:

        virtual void calculatePositionAndSize();
        virtual void setP2(int x, int y);
        virtual void calibrate();
};

#endif // MODLOWGRADEWINDOW_H
