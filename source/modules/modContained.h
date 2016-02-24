#ifndef MODCONTAINED_H
#define MODCONTAINED_H

#include "general.h"
#include "Module.h"

class modContained : public Module
{
    public:
        modContained(){}
        virtual ~modContained(){}

    public:
        virtual bool isValidPosition(std::vector<Module*> modules);
};

#endif // MODCONTAINED_H
