#pragma once
#include "Agate/Events/Event.h"

namespace Agate
{
    class WindowResizedEvent : public Event {
    public:
        WindowResizedEvent(int x, int y)
            : m_xSize(x), m_ySize(y)
        {
        }

        EventTypes GetEventType() override
        {
            return EventTypes::WindowResized;
        }

        void PrintEventName() override
        {
            std::string eventString = "WindowResized to: " + std::to_string(m_xSize) + ", " + std::to_string(m_ySize);
            PRINTMSG(eventString);
        }

        bool Handled() override
        {
            return this->EventFinised;
        }

        static EventTypes s_GetEventType()
        {
            return EventTypes::WindowResized;
        }

    private:
        int m_xSize, m_ySize;
    };

    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent()
        {
        }

        EventTypes GetEventType() override
        {
            return EventTypes::WindowClose;
        }

        void PrintEventName() override
        {
            std::string eventString = "Window Closing";
            PRINTMSG(eventString);
        }

        bool Handled() override
        {
            return this->EventFinised;
        }

        static EventTypes s_GetEventType()
        {
            return EventTypes::WindowClose;
        }
    };
}// namespace Agate
