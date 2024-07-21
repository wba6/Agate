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
            PRINTMSG("Window Resized to: {}, {}", m_xSize, m_ySize);
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
            PRINTMSG("Window Closing");
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
