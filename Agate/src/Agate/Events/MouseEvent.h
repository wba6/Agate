#pragma once
#include "Event.h"
namespace Agate
{
    class API MouseButtonPressed : public Event {
    public:
        MouseButtonPressed(int button)
            : m_button(button)
        {}

        EventTypes GetEventType() override
        {
            return EventTypes::MouseButtonPressed;
        }
        void PrintEventName() override
        {
            std::string eventString = "MousePressed button: " + std::to_string(m_button);
            PRINTMSG(eventString);
        }
        bool Handled() override
        {
            return this->EventFinised;
        }

        static EventTypes s_GetEventType()
        {
            return EventTypes::MouseButtonPressed;
        }

    private:
        int m_button;
    };

    class API MouseButtonReleased : public Event {
    public:
        MouseButtonReleased(int button)
            : m_button(button)
        {}

        EventTypes GetEventType() override
        {
            return EventTypes::MouseButtonReleased;
        }
        void PrintEventName() override
        {
            std::string eventString = "MouseReleased button: " + std::to_string(m_button);
            PRINTMSG(eventString);
        }
        bool Handled() override
        {
            return this->EventFinised;
        }

        static EventTypes s_GetEventType()
        {
            return EventTypes::MouseButtonReleased;
        }

    private:
        int m_button;
    };
}// namespace Agate
