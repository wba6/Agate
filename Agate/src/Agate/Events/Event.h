#pragma once

#include "../Core.h"
#include "../Logger.h"

#include <functional>

namespace Agate
{

    enum class EventTypes {
        MouseClick,
        MouseRelease,
        MouseMoved,
        KeyPressed,
        KeyReleased
    };

    class API Event {
        friend class EventNotifier;

    public:
        Event()
            : EventFinised(false) {}
        virtual EventTypes GetEventType() = 0;
        virtual void PrintEventName() = 0;
        virtual void Recived() = 0;
        virtual bool Handled() = 0;
        virtual void SetCallBackFunc(std::function<void(Event &)> func) = 0;

    protected:
        bool EventFinised;
    };

    class API EventNotifier {
    public:
        EventNotifier() = default;

        void NotifyEvent(Event &ev)
        {
            if (!(ev.Handled()))
            {
                ev.Recived();
            }
        }
    };


}// namespace Agate
