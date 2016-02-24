#include "CustomBuildingBlock.h"

// ths has some literals that could be gotten rid of
void CustomBuildingBlock::render()
{
    // do not render these types
    if (type == INTERIOR) return;

    std::vector<Point>  cornerPoints;
    for (int i = 0; i <= 90; ++i)
    {
        int startx1 = 100;
        int starty1 = 0;
        Point p1;

        int startx2 = 125;
        int starty2 = 0;
        Point p2;

        float theta = static_cast<float>(i) * DEGTORAD;

        p1.x = startx1 * cos(theta) - starty1 * sin(theta);
        p1.y = startx1 * sin(theta) + starty1 * cos(theta);
        p1.x -= 100;
        p1.y -= 100;
        cornerPoints.push_back(p1);

        p2.x = startx2 * cos(theta) - starty2 * sin(theta);
        p2.y = startx2 * sin(theta) + starty2 * cos(theta);
        p2.x -= 100;
        p2.y -= 100;
        cornerPoints.push_back(p2);
    }

    int tx = box.x;
    int ty = box.y;

    if (angle == 0 or angle == 270) {
        tx += UNIT;
    } else {
        tx += HIGH_GRADE_SIZE;
    }

    if (angle == 0 or angle == 90) {
        ty += UNIT;
    } else {
        ty += HIGH_GRADE_SIZE;
    }

    glPushMatrix();
    glTranslated(tx,ty,0);
    glRotated(angle,0,0,1);
    glBegin(GL_TRIANGLE_STRIP);
        for (unsigned i = 0; i < cornerPoints.size(); ++i)
        {
            glVertex2f(cornerPoints.at(i).x,cornerPoints.at(i).y);
        }
    glEnd();
    glPopMatrix();
}

