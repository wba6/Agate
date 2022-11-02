#pragma once
#include "Event.h"
namespace Agate
{
    class MouseMoved : public Event {
    public:
        MouseMoved(int x, int y)
            : m_newXPos(x), m_newYPos(y)
        {}


        EventTypes GetEventType() override
        {
            return EventTypes::MouseMoved;
        }


        void PrintEventName() override
        {
            std::string eventString = "MouseMoved to: " + std::to_string(m_newXPos) + ", " + std::to_string(m_newYPos);
            PRINTMSG(eventString);
        }
        int GetXPos()
        {
            return m_newXPos;
        }
        int GetYPos()
        {
            return m_newYPos;
        }
        bool Handled() override
        {
            return this->EventFinised;
        }

        static EventTypes s_GetEventType()
        {
            return EventTypes::MouseMoved;
        }

    private:
        int m_newXPos, m_newYPos;
    };

    class MouseButton : public Event {
    protected:
        MouseButton(int button)
            : m_button(button)
        {}
        int m_button;
    };

    class API MouseButtonPressed : public MouseButton {
    public:
        MouseButtonPressed(int button)
            : MouseButton(button)
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
    };

    class API MouseButtonReleased : public MouseButton {
    public:
        MouseButtonReleased(int button)
            : MouseButton(button)
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
    };
}// namespace Agate
