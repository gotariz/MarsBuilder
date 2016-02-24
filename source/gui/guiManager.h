#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "general.h"
#include "guiElement.h"
#include "guiPanel.h"
#include "guiButton.h"
#include "guiLabel.h"

class guiManager
{
    public:
        guiManager(){}
        virtual ~guiManager(){}

        void freeResources();

        guiButton*  createButton(int id = -1);
        guiPanel*   createPanel(int id = -1);
        guiLabel*   createLabel(int id = -1);

        void        removeElement(int id);
        guiElement* getElementByID(int id);

        void draw();
        void updateGUIElements();
        void untoggle(int id, int group);
        bool pollEvent(guiEvent &event);

        bool handleMouseMoveEvents(int x, int y);
        void handleMouseDragEvents(int x, int y);
        void handleMouseClickEvents(int button, int state, int x, int y);

    protected:
        int                         m_next_id = 1;
        std::vector<guiEvent>       m_events;
        std::vector<guiElement*>    m_elements;

};

#endif // GUIMANAGER_H
