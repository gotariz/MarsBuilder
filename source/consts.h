#ifndef CONSTS_H_INCLUDED
#define CONSTS_H_INCLUDED

#include "glib.h"
using namespace glib;

static const float PI = 3.1415926535897932;
static const float DEGTORAD = PI / 180.f;
static const float RADTODEG = 180.f / PI;

static const int    DEFAULT_WIDTH = 1280;
static const int    DEFAULT_HEIGHT = 720;

static const int    TOOLBARSIZE = 32;
static const int    ICONSIZE = 32;
static const int    CROSSHAIRSIZE = 5;

static const int    UNIT            = 100; // 1 unit in the world is equivelent to 100 pixels on the screen and 100% zoom
static const int    HALF_UNIT       = UNIT / 2;
static const int    QUARTER_UNIT    = UNIT / 4;

static const float  ZOOM_INCREMENT  = 0.1f;

static const int    GRID_SIZE       = UNIT / 4;
static const int    LOW_GRADE_SIZE  = UNIT / 2;
static const int    HIGH_GRADE_SIZE = UNIT / 4;

static const Colour C_RED_TRANSPARENT(1.f,0.f,0.f,0.5f);
static const Colour C_GREEN_TRANSPARENT(0.f,1.f,0.f,0.5f);
static const Colour C_BLUE_TRANSPARENT(0.f,0.f,1.f,0.5f);
static const Colour C_RED(1.f,0.f,0.f,1.f);
static const Colour C_GREEN(0.f,1.f,0.f,1.f);
static const Colour C_BLUE(0.f,0.f,1.f,1.f);
static const Colour C_GREY(0.5f,0.5f,0.5f,1.f);
static const Colour C_BLACK(0.f,0.f,0.f,1.f);
static const Colour C_WHITE(1.f,1.f,1.f,1.f);
static const Colour C_DARK_GREY(0.2f,0.2f,0.2f,1.f);

static const Colour C_X_AXIS(0.86f,0.18f,0.18f);
static const Colour C_Y_AXIS(0.08f,0.59f,0.8f);
static const Colour C_GRID(0.85f,0.85f,0.85f);


#endif // CONSTS_H_INCLUDED
