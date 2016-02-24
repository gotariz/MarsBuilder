#ifndef GLIB_H_INCLUDED
#define GLIB_H_INCLUDED

#include "dependencies.h"

namespace glib {

class Colour {
    public:
        Colour(float _r = 1.f, float _g = 1.f, float _b = 1.f, float _a = 1.f) : r(_r), g(_g), b(_b), a(_a) {}
    public:
        float r;
        float g;
        float b;
        float a;

        void set(float _r = 1.f, float _g = 1.f, float _b = 1.f, float _a = 1.f) {
            r = _r;
            g = _g;
            b = _b;
            a = _a;
        }

        //operators
        void operator=(const Colour &colour) {
            r = colour.r;
            g = colour.g;
            b = colour.b;
            a = colour.a;
        }
};

class Dimension {
    public:
        Dimension(int _w = 0, int _h = 0) : w(_w), h(_h){}
        virtual ~Dimension(){}
    public:
        int w;
        int h;

        void set(int _w, int _h) {
            w = _w;
            h = _h;
        }
};

class Point {
    public:
        Point(int _x = 0, int _y = 0) : x(_x), y(_y){}
        virtual ~Point(){}
    public:
        int x;
        int y;

        void set(int _x, int _y) {
            x = _x;
            y = _y;
        }

        Point subtracted(Point p)
        {
            return Point(x - p.x, y - p.y);
        }

        Point added(Point p)
        {
            return Point(x + p.x, y + p.y);
        }

        bool operator==(const Point &p) const {
            return (x == p.x and y == p.y);
        }
};

class Pointf {
    public:
        Pointf(float _x = 0, float _y = 0) : x(_x), y(_y){}
        virtual ~Pointf(){}
    public:
        float x;
        float y;

        void set(float _x, float _y) {
            x = _x;
            y = _y;
        }
};

class Rec
{
    public:
        Rec(int _x = 0, int _y = 0, int _w = 0, int _h = 0) : x(_x), y(_y), w(_w), h(_h) {}
        virtual ~Rec(){}

        //operators
        void operator=(const Rec &rec) {
            x = rec.x;
            y = rec.y;
            w = rec.w;
            h = rec.h;
        }

    public:
        int x;
        int y;
        int w;
        int h;

        void set(int _x, int _y, int _w, int _h) {
            x = _x;
            y = _y;
            w = _w;
            h = _h;
        }

        void setPosition(int _x, int _y){
            x = _x;
            y = _y;
        }

        void setSize(int _w, int _h){
            w = _w;
            h = _h;
        }

        void translate(int _x, int _y) {
            x += _x;
            y += _y;
        }
};

}

#endif // GLIB_H_INCLUDED
