#include "guiManager.h"

void guiManager::freeResources()
{
    for (unsigned i = 0; i < m_elements.size(); ++i)
    {
        guiElement* element = m_elements.at(i);
        element->freeResources();
        delete element;
    }

    m_elements.clear();
}

guiButton* guiManager::createButton(int id)
{
    guiButton* btn = new guiButton(id);
    m_elements.push_back(btn);
    return btn;
}

guiPanel* guiManager::createPanel(int id)
{
    guiPanel* pnl = new guiPanel(id);
    m_elements.push_back(pnl);
    return pnl;
}

guiLabel* guiManager::createLabel(int id)
{
    guiLabel* lbl = new guiLabel(id);
    m_elements.push_back(lbl);
    return lbl;
}

bool guiManager::pollEvent(guiEvent &event)
{
    if (m_events.size() == 0) return false;

    event = m_events.at(0);
    m_events.erase(m_events.begin());
    return true;
}

void guiManager::removeElement(int id)
{
    std::vector<guiElement*>::iterator it = m_elements.begin();

    while (it != m_elements.end()) {
        if ((*it)->getID() == id) {
            delete (*it);
            m_elements.erase(it);
        }
    }
}

guiElement* guiManager::getElementByID(int id)
{
    for (unsigned i = 0; i < m_elements.size();++i)
    {
        if (m_elements.at(i)->getID() == id)
            return m_elements.at(i);
    }
    return nullptr;
}

bool guiManager::handleMouseMoveEvents(int x, int y)
{
    // loop from end to beginging
    bool redisplay = false;
    guiElement* element = nullptr;

    for (int i = m_elements.size() - 1; i >= 0; --i) {
        element = m_elements.at(i);

        if (element->isPointTouching(Point(x,y))) {
            element->onEnter();
        } else {
            element->onExit(); // more like if not mouse over
        }
    }

    return redisplay;
}

void guiManager::handleMouseDragEvents(int x, int y)
{
    for (unsigned i = 0; i < m_elements.size(); ++i) {
        guiElement* element = m_elements.at(i);

        if (element->isPointTouching(Point(x,y))) {
            element->onDragEnter();
        } else {
            element->onDragExit(); // more like if not mose drag over
        }
    }
}

void guiManager::handleMouseClickEvents(int button, int state, int x, int y)
{
    for (signed i = m_elements.size() - 1; i >= 0; --i) {
        guiElement* element = m_elements.at(i);
        // ignore the element if the mouse is not over it
        if (!element->isPointTouching(Point(x,y))) continue;

        // mouse buttons
        if (button == MOUSE_LEFT and state == PRESSED) {                        // left mouse pressed
            element->onMouseDown();
        } else if (button == MOUSE_LEFT and state == RELEASED) {                // left mouse released
            if (element->m_state == ACTIVE or element->m_state == TOGGLED) {
                element->onMouseUp();
                int state = CLICKED;
                // untoggle other toggles in the group
                if (element->m_isToggle and element->m_state == TOGGLED){
                    untoggle(element->m_id,element->m_group);
                    state = TOGGLED_ON;
                } else if (element->m_isToggle and element->m_state == HOVER) {
                    state = TOGGLED_OFF;
                }

                m_events.push_back(guiEvent(element->getID(),state));
            }
        }
    } // end of for loop
}

// untoggle all except the one with the passed in ID
void guiManager::untoggle(int id, int group)
{
    guiElement* element = nullptr;
    for (unsigned i = 0; i < m_elements.size(); ++i)
    {
        element = m_elements.at(i);
        if (element->m_group == group and element->m_id != id) {
            element->m_state = IDLE;
        }
    }
}

void guiManager::draw()
{
    for (unsigned i = 0; i < m_elements.size(); ++i) {
        guiElement* element = m_elements.at(i);

        int x = element->m_actualPosition.x + globals.rCamera.x;
        int y = element->m_actualPosition.y + globals.rCamera.y;

        if (element->v_anchor == TOP)   {y = globals.rCamera.h - element->m_position.y;}
        else                            {y = element->m_position.y;}

        if (element->h_anchor == RIGHT) {x = globals.rCamera.w - element->m_position.x;}
        else                            {x = element->m_position.x;}

        element->m_actualPosition.set(x,y);
        element->draw();
    }
}

void guiManager::updateGUIElements()
{
    for (unsigned i = 0; i < m_elements.size(); ++i) {
        guiElement* element = m_elements.at(i);

        int newWidth = element->m_size.w;
        int newHeight = element->m_size.h;

        if (element->m_relative_h.m_isRelative) {
            float relHeight = (element->m_relative_h.m_amount / 100.f) * static_cast<float>(globals.rScreen.h);
            newHeight = relHeight + element->m_size.h;
        }
        if (element->m_relative_w.m_isRelative) {
            float relWidth = (element->m_relative_w.m_amount / 100.f) * static_cast<float>(globals.rScreen.w);
            newWidth = relWidth + element->m_size.w;
        }

        element->m_actualSize.set(newWidth,newHeight);
    }
}
