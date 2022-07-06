#pragma once

#include "../Agate/Logger.h"
#include "../Agate/Core.h"
namespace Agate
{

    enum class EventTypes {
        MouseClick, MouseRelease,MouseMoved,
        KeyPressed, KeyReleased
    };

    class API Event {
        friend class EventClassifier;
    public:
        Event()
            : EventFinised(false) {}
        virtual EventTypes GetEventType() = 0;
        virtual void PrintEventName() = 0;
        virtual void Recived() = 0;
        virtual bool Handled() = 0;
    protected:
        bool EventFinised;
    };

    class API EventClassifier {
    public:
        EventClassifier(Event &ev)
            : event(ev) {
            if (!(event.Handled())) {
                event.Recived();
            }
        }

    private:
        Event &event;
    };

  
}
