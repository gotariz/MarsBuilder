#include "modContained.h"

bool modContained::isValidPosition(std::vector<Module*> modules)
{
    bool isContained = false;
    bool isColliding = false;

    // check all modules
    for (unsigned i = 0; i < modules.size(); ++i)
    {
        // check all blocks in that module
        Module* m = modules.at(i);
        for (unsigned j = 0; j < m->getBlocks()->size(); ++j)
        {
            // check all blocks against the blocks in this module
            BuildingBlock* b2 = m->getBlocks()->at(j);
            for (unsigned k = 0; k < blocks.size(); ++k)
            {
                BuildingBlock* b1 = blocks.at(k);
                if (b1->isColliding(b2)) isColliding = true;
                if (b1->isContained(b2)) isContained = true;
            }

        }
    }

    return (isContained and !isColliding);
}
