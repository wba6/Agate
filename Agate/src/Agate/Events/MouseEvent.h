#pragma once
#include "Event.h"
#include <string>
namespace Agate
{
    class API MouseClick : public Event {
    public:
        using EventFn = std::function<void(Event &)>;
        MouseClick(int xpos,int ypos) 
        : xPos(xpos), yPos(ypos)
        {}

        EventTypes GetEventType() override
        {
            return EventTypes::MouseClick;
        }
        void PrintEventName() override
        {
            std::string eventString = "MouseClick at: " + std::to_string(xPos) + " " + std::to_string(yPos);
            PRINTMSG(eventString);
        }
        void Recived() override
        {
            PRINTMSG("Recvied Mouse Click");

            if (s_callback != nullptr) 
                s_callback(*this);
            
            EventFinised = true;
        }
        bool Handled() override
        {
            return this->Event::EventFinised;
        }
        void SetCallBackFunc(EventFn func) override
        {
            s_callback = func;
        }
        const int& GetxPos() const{
            return xPos;
        }
        const int& GetyPos() const
        {
            return yPos;
        }

    private:
        int xPos, yPos;
        static EventFn s_callback;
    };
}// namespace Agate
