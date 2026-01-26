/**
 * @brief Include file for mouse input events
 */

#ifndef AGATE_MOUSEEVENT_H
#define AGATE_MOUSEEVENT_H

#include "Event.h"

namespace Agate {

    /**
     * @brief Emitted when the mouse cursor moves in the application
     *        window
     */
    class MouseMoved : public Event {
    public:

        /**
         * @brief Constructor - Takes the new cursor coordinates
         * 
         * @param x New X coordinate of the cursor
         * @param y New Y coordinate of the cursor
         */
        MouseMoved(int x, int y)
                : m_newXPos(x), m_newYPos(y) {}

        /**
         * @brief Type of this event
         */
        EventTypes GetEventType() override {
            return EventTypes::MouseMoved;
        }

        /**
         * @brief Prints the name of this event
         */
        void PrintEventName() override {
            PRINTMSG("MouseMoved to: {}, {}", m_newXPos, m_newYPos);
        }

        /**
         * @brief New X coordinate of the cursor
         * 
         * @return X coordinate of the cursor
         */
        int GetXPos() {
            return m_newXPos;
        }

        /**
         * @brief New Y coordinate of the cursor
         * 
         * @return Y coordinate of the cursor
         */
        int GetYPos() {
            return m_newYPos;
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
            return EventTypes::MouseMoved;
        }

    private:
        int m_newXPos, m_newYPos;
    };

    /**
     * @brief Parent for all mouse button events
     */
    class MouseButton : public Event {
    protected:

        /**
         * @brief Constructor - Takes an integer representation
         *        of the emitting mouse button
         */
        MouseButton(int button)
                : m_button(button) {}

        int m_button;
    };

    class API MouseButtonPressed : public MouseButton {
    public:

        /**
         * @brief Constructor - Takes an integer representation
         *        of the emitting mouse button
         */
        MouseButtonPressed(int button)
                : MouseButton(button) {}

        /**
         * @brief Type of this event
         */
        EventTypes GetEventType() override {
            return EventTypes::MouseButtonPressed;
        }

        /**
         * @brief Prints the name of this event
         */
        void PrintEventName() override {
            std::string eventString = "MousePressed button: " + std::to_string(m_button);
            PRINTMSG("MousePressed button: {}", m_button);
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
            return EventTypes::MouseButtonPressed;
        }
    };

    class API MouseButtonReleased : public MouseButton {
    public:

        /**
         * @brief Constructor - Takes an integer representation
         *        of the emitting mouse button
         */
        MouseButtonReleased(int button)
                : MouseButton(button) {}

        /**
         * @brief Type of this event
         */
        EventTypes GetEventType() override {
            return EventTypes::MouseButtonReleased;
        }

        /**
         * @brief Prints the name of this event
         */
        void PrintEventName() override {
            PRINTMSG("MouseReleased button: {}", m_button);
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
            return EventTypes::MouseButtonReleased;
        }
    };
} // namespace Agate

#endif // AGATE_MOUSEEVENT_H
