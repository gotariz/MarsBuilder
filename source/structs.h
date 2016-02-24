#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "enums.h"
#include "glib.h"
using namespace glib;
class Module;

struct UndoEvent {
    int     type;
    Module* module;
    Point   oldPosition;
    Point   oldSize;
    int     oldOrientation;

    UndoEvent(int t, Module* m) : type(t), module(m){}
};

struct guiEvent {
    int id;
    int state;

    guiEvent(int a = 0, int b = 0) : id(a), state(b) {}

    void operator=(const guiEvent &event) {
        id      = event.id;
        state   = event.state;
    }
};

struct Pair {
    int id;
    std::string path;

    Pair(int a, std::string b) : id(a), path(b) {}
};

struct RelativeSize {
    bool    m_isRelative;
    float   m_amount;

    RelativeSize(bool _relative = false, float _amount = 100) : m_isRelative(_relative), m_amount(_amount) {}

    void set(bool _relative = false, float _amount = 100)
    {
        m_isRelative = _relative;
        m_amount = _amount;
    }
};

#endif // STRUCTS_H_INCLUDED
