//
// Created by TANK1_41 on 8/23/2022.
//
#include "Event.h"
#pragma once
namespace Agate{
    class KeyPressed : public Event {
    public:
        KeyPressed(int keyCode)
                :m_keycode(keyCode){};

        EventTypes GetEventType() override
        {
            return EventTypes::KeyPressed;
        }
        void PrintEventName() override
        {
            std::string eventString = "KeyPressed: " + std::to_string(m_keycode);
            PRINTMSG(eventString);
        }
        bool Handled() override
        {
            return this->EventFinised;
        }
    private:
        unsigned int m_keycode;
    };

    class KeyReleased : public Event {
    public:
        KeyReleased(int keyCode)
            :m_keycode(keyCode){};

        EventTypes GetEventType() override
        {
            return EventTypes::KeyReleased;
        }
        void PrintEventName() override
        {
            std::string eventString = "KeyReleased: " + std::to_string(m_keycode);
            PRINTMSG(eventString);
        }
        bool Handled() override
        {
            return this->EventFinised;
        }
    private:
        unsigned int m_keycode;
    };
}

