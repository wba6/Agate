#pragma once
#include "Event.h"

namespace Agate
{
    class API MouseClick : public Event {
        using EventFn = std::function<void()>;

    public:
        MouseClick() {}

        EventTypes GetEventType() override
        {
            return EventTypes::MouseClick;
        }
        void PrintEventName() override
        {
            PRINTMSG("MouseClick");
        }
        void Recived() override
        {
            PRINTMSG("Recvied Mouse Click");
            callback();
            EventFinised = true;
        }
        bool Handled() override
        {
            return Event::EventFinised;
        }
        void SetCallBackFunc(std::function<void()> func) override
        {
            callback = func;
        }

    private:
        EventFn callback;
    };
}// namespace Agate
