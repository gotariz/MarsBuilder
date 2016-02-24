#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <iostream>
#include <sstream>
#include <fstream>

#include "glib.h"
#include "consts.h"
#include "globals.h"

using namespace glib;
extern Globals globals;

namespace utils {

    // function declarations
    void drawRectangle(int x1, int y1, int x2, int y2, Colour c);
    void drawRectangle(Rec r, Colour c);
    void drawRectangleOutline(Rec r, Colour c);
    bool isContained(Point p, Rec r);
    bool isContained(Rec r1, Rec r2);
    bool isOverlapping(Rec r1, Rec r2);

    Point getCrosshairWorldPosition(int x, int y);
    Point glGetMouseCoordinates(int x, int y);
    Point getMouseWorldCoordinatesCanvas(int x, int y);
    Point getMouseWorldCoordinatesScreen(int x, int y);
    Point worldToCanvas(int x, int y);

    int     roundUp(int numToRound, int multiple);
    int     roundNearest(int numToRound, int multiple);
    float   roundNearestf(float numToRound, int multiple);

    void print(std::string messge);
    void print(std::string messge, float value);

    void glSetColour(Colour c);

    template<typename T>
    std::string toString( const T& value );


    ///////////////////////////////////////////////////////////////////////
    // Inline implementations
    ///////////////////////////////////////////////////////////////////////
    inline void glSetColour(Colour c) {
        glColor4f(c.r,c.g,c.b,c.a);
    }

    template<typename T>
    inline std::string toString( const T& value )
    {
        std::ostringstream oss;
        try {
            // Turn on exceptions
            oss.exceptions( std::ios::badbit | std::ios::failbit );
            oss << value;
        } catch ( std::ios_base::failure e ) {
            std::cerr << e.what() << std::endl;
            oss.clear( std::ios::goodbit );
            return "";
        }

        return oss.str();
    }


    inline void print(std::string message) {
        std::cout << message << std::endl;
    }

    inline void print(std::string message, float value) {
        std::cout << message << value << std::endl;
    }

    inline void drawRectangle(int x1, int y1, int x2, int y2, Colour c) {
        glColor4f(c.r,c.g,c.b,c.a);
        glBegin(GL_QUADS);
            glVertex2f(x1,y1);
            glVertex2f(x2,y1);
            glVertex2f(x2,y2);
            glVertex2f(x1,y2);
        glEnd();
    }

    inline void drawRectangle(Rec r, Colour c) {
        glColor4f(c.r,c.g,c.b,c.a);
        glBegin(GL_QUADS);
            glVertex2f(r.x,r.y);
            glVertex2f(r.x + r.w,r.y);
            glVertex2f(r.x + r.w,r.y + r.h);
            glVertex2f(r.x,r.y + r.h);
        glEnd();
    }

     inline void drawRectangleOutline(Rec r, Colour c) {
        glColor4f(c.r,c.g,c.b,c.a);
        glBegin(GL_LINE_LOOP);
            glVertex2f(r.x,r.y);
            glVertex2f(r.x + r.w,r.y);
            glVertex2f(r.x + r.w,r.y + r.h);
            glVertex2f(r.x,r.y + r.h);
        glEnd();
    }

    inline bool isContained(Rec r1, Rec r2) {
        if (r1.x < r2.x)                return false; // outside on the left
        if (r1.y < r2.y)                return false; // outside on the bottom
        if (r1.x + r1.w > r2.x + r2.w)  return false; // outside on the right
        if (r1.y + r1.h > r2.y + r2.h)  return false; // outside on the top

        return true;
    }

    inline bool isContained(Point p, Rec r) {
        if (p.x < r.x)                return false; // outside on the left
        if (p.y < r.y)                return false; // outside on the bottom
        if (p.x > r.x + r.w)         return false;  // outside on the right
        if (p.y > r.y + r.h)         return false;  // outside on the top

        return true;
    }

    inline bool isOverlapping(Rec r1, Rec r2) {

        if (r1.x + r1.w <= r2.x) return false; // r1 is too far left to overlap
        if (r1.y + r1.h <= r2.y) return false; // r1 is too far below to overlap
        if (r1.x >= r2.x + r2.w) return false; // r1 is to far right to overlap
        if (r1.y >= r2.y + r2.h) return false; // r1 is to far above to overlap

        return true; // they are overlapping
    }

    inline Point getMouseWorldCoordinatesScreen(int x, int y) {

        float xRatio = static_cast<float>(x) / globals.rScreen.w;
        float yRatio = static_cast<float>(y) / globals.rScreen.h;

        Point newPosition;

        newPosition.x = (globals.rCamera.w * xRatio) + globals.rCamera.x;
        newPosition.y = (globals.rCamera.h * yRatio) + globals.rCamera.y;

        return newPosition;
    }

    inline Point getMouseWorldCoordinatesCanvas(int x, int y) {
        x -= globals.rCanvas.x;

        float xRatio = static_cast<float>(x) / static_cast<float>(globals.rCanvas.w);
        float yRatio = static_cast<float>(y) / static_cast<float>(globals.rCanvas.h);

        float newX = (static_cast<float>(globals.rCameraCanvas.w) * xRatio) + static_cast<float>(globals.rCameraCanvas.x);
        float newY = (static_cast<float>(globals.rCameraCanvas.h) * yRatio) + static_cast<float>(globals.rCameraCanvas.y);

        return Point(newX,newY);
    }

    inline Point glGetMouseCoordinates(int x, int y) {
        y = globals.rScreen.h - y;

        return glib::Point(x,y);
    }

    // pass in mouse world co-ordinates
    inline Point getCrosshairWorldPosition(int x, int y) {

        Point cp = Point(x,y);

        cp.x = roundNearest(cp.x,GRID_SIZE);
        cp.y = roundNearest(cp.y,GRID_SIZE);

        return cp;
    }

    inline Point worldToCanvas(int x, int y)
    {
        float wx = x - globals.rCameraCanvas.x;
        float wy = y - globals.rCameraCanvas.y;

        float xratio = wx / globals.rCameraCanvas.w;
        float yratio = wy / globals.rCameraCanvas.h;

        int canvasx = roundNearestf(xratio * globals.rCanvas.w,1);
        int canvasy = roundNearestf(yratio * globals.rCanvas.h,1);

        return Point(canvasx, canvasy);
    }

    inline int roundNearest(int numToRound, int multiple) {
        int remainder = numToRound % multiple;

        if (remainder < 0) {
            if (remainder >= -(multiple / 2) )  return numToRound - remainder;
            else                                return numToRound - (multiple + remainder);
        } else if (remainder > 0) {
            if (remainder >= (multiple / 2) )   return numToRound + (multiple - remainder);
            else                                return numToRound - remainder;
        } else {
            return numToRound; // already a multiple
        }
    }

    inline float roundNearestf(float numToRound, int multiple) {

        int numToRoundi = numToRound;
        float remainder = (numToRoundi % multiple);
        remainder += numToRound - static_cast<float>(numToRoundi);

        if (remainder < 0) {
            if (remainder >= -(multiple / 2) )  return numToRound - remainder;
            else                                return numToRound - (multiple + remainder);
        } else if (remainder > 0) {
            if (remainder >= (multiple / 2) )   return numToRound + (multiple - remainder);
            else                                return numToRound - remainder;
        } else {
            return numToRound; // already a multiple
        }

        return remainder;
    }

    inline int roundUp(int numToRound, int multiple)
    {
        if (multiple == 0)
            return numToRound;

        int remainder = abs(numToRound) % multiple;
        if (remainder == 0)
            return numToRound;
        if (numToRound < 0)
            return -(abs(numToRound) - remainder);

        return numToRound + multiple - remainder;
    }

}

#endif // UTILS_H_INCLUDED
