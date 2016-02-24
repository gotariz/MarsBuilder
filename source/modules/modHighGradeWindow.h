#ifndef MODHIGHGRADEWINDOW_H
#define MODHIGHGRADEWINDOW_H

#include "modContained.h"


class modHighGradeWindow : public modContained
{
    public:
        modHighGradeWindow(){
            minSize         = QUARTER_UNIT;
            maxSize         = UNIT + HALF_UNIT;
            incrementSize   = QUARTER_UNIT;

            movable = true;
            resizable = true;

            type = M_HIGH_GRADE_WINDOW;
        }
        virtual ~modHighGradeWindow(){}

    public:

        virtual void setP2(int x, int y);
        virtual void calibrate();
        virtual void rotate(){}
};

#endif // MODHIGHGRADEWINDOW_H
