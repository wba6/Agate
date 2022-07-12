#pragma once
#include "Event.h"
#include <string>
namespace Agate
{
    class API MouseClick : public Event {
    public:
        MouseClick(int xpos, int ypos)
            : m_xPos(xpos), m_yPos(ypos)
        {}

        EventTypes GetEventType() override
        {
            return EventTypes::MouseClick;
        }
        void PrintEventName() override
        {
            std::string eventString = "MouseClick at: " + std::to_string(m_xPos) + " " + std::to_string(m_yPos);
            PRINTMSG(eventString);
        }
        bool Handled() override
        {
            return this->EventFinised;
        }

        const int &GetxPos() const
        {
            return m_xPos;
        }
        const int &GetyPos() const
        {
            return m_yPos;
        }

        static EventTypes s_GetEventType()
        {
            return EventTypes::MouseClick;
        }

    private:
        int m_xPos, m_yPos;
    };


}// namespace Agate
