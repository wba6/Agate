//
// Created by TANK1_41 on 8/23/2022.
//
#include "Event.h"
#pragma once
namespace Agate{
    class KeyPressedEvent : public Event {
    public:
        KeyPressedEvent(int keyCode)
                :m_keycode(keyCode){};

        EventTypes GetEventType() override
        {
            return EventTypes::KeyPressed;
        }
        void PrintEventName() override
        {
            std::string eventString = "KeyPressedEvent: " + std::to_string(m_keycode);
            PRINTMSG(eventString);
        }
        bool Handled() override
        {
            return this->EventFinised;
        }
        static EventTypes s_GetEventType()
        {
            return EventTypes::KeyPressed;
        }
    private:
        unsigned int m_keycode;
    };

    class KeyReleasedEvent : public Event {
    public:
        KeyReleasedEvent(int keyCode)
            :m_keycode(keyCode){};

        EventTypes GetEventType() override
        {
            return EventTypes::KeyReleased;
        }
        void PrintEventName() override
        {
            std::string eventString = "KeyReleasedEvent: " + std::to_string(m_keycode);
            PRINTMSG(eventString);
        }
        bool Handled() override
        {
            return this->EventFinised;
        }
        static EventTypes s_GetEventType()
        {
            return EventTypes::KeyReleased;
        }
    private:
        unsigned int m_keycode;
    };
}

