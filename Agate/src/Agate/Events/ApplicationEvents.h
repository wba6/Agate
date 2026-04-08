/**
 * @brief Include file for application/window level events
 */

#ifndef AGATE_APPLICATIONEVENTS_H
#define AGATE_APPLICATIONEVENTS_H

#include "Agate/Events/Event.h"

namespace Agate {

    /**
     * @brief Emitted when the application window is resized.
     *        Has the new window size
     */
    class WindowResizedEvent : public Event {
    public:

        /**
         * @brief Constructor - takes the new dimensions of
         *        the window
         * 
         * @param x New width of the window
         * @param y New height of the window
         */
        WindowResizedEvent(int x, int y)
                : m_xSize(x), m_ySize(y) {
        }

        /**
         * @brief Type of this event
         */
        EventTypes GetEventType() override {
            return EventTypes::WindowResized;
        }

        /**
         * @brief Prints the name of this event
         */
        void PrintEventName() override {
            PRINTMSG("Window Resized to: {}, {}", m_xSize, m_ySize);
        }

        /**
         * @brief Predicate for whether the event has
         *        been fully handled
         */
        bool Handled() override {
            return this->EventFinised;
        }

        /**
         * @brief Type of this event
         */
        static EventTypes s_GetEventType() {
            return EventTypes::WindowResized;
        }

        /**
         * @brief Accessor for the new window dimensions
         */
        inline std::pair<int, int> GetWindowSize() const {
            return {m_xSize, m_ySize};
        }

    private:
        int m_xSize, m_ySize;
    };

    /**
     * @brief Emitted when the application window is closed
     */
    class WindowCloseEvent : public Event {
    public:

        WindowCloseEvent() {
        }

        /**
         * @brief Type of this event
         */
        EventTypes GetEventType() override {
            return EventTypes::WindowClose;
        }

        /**
         * @brief Prints the name of this event
         */
        void PrintEventName() override {
            PRINTMSG("Window Closing");
        }

        /**
         * @brief Predicate for whether the event has
         *        been fully handled
         */
        bool Handled() override {
            return this->EventFinised;
        }

        /**
         * @brief Type of this event
         */
        static EventTypes s_GetEventType() {
            return EventTypes::WindowClose;
        }
    };
}// namespace Agate

#endif // AGATE_APPLICATIONEVENTS_H
