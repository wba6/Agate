#pragma once
#include "agpch.h"

#include "../Core.h"
#include "../Logger.h"


namespace Agate
{

    enum class API EventTypes {
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        KeyPressed,
        KeyReleased,
        WindowResized,
        WindowClose

    };

    class API Event {
        friend class EventNotifier;

    public:
        Event()
            : EventFinised(false) {}
        virtual EventTypes GetEventType() = 0;
        virtual void PrintEventName() = 0;
        virtual bool Handled() = 0;

    protected:
        bool EventFinised;
    };

    class API EventNotifier {
        template<typename T>
        using EventFn = std::function<bool(T &)>;

    public:
        EventNotifier(Event &e)
            : m_Event(e){};

        template<typename T>

        bool NotifyEvent(EventFn<T> ev)
        {
            if (m_Event.GetEventType() == T::s_GetEventType())
            {
                m_Event.EventFinised = ev(*(T *) &m_Event);
                return true;
            }
            return false;
        }

    private:
        Event &m_Event;
    };


}// namespace Agate
