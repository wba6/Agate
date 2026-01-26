/**
 * @brief Include file for keyboard input events
 * 
 * Created by TANK1_41 on 8/23/2022.
 */

#include "Event.h"

#ifndef AGATE_KEYEVENTS_H
#define AGATE_KEYEVENTS_H

namespace Agate {

    /**
     * @brief Emitted when any key is pressed
     */
    class KeyPressedEvent : public Event {
    public:

        /**
         * @brief Constructor - takes a keycode to identify the
         *        pressed key
         * 
         * @param keyCode Keycode representing the pressed key
         */
        KeyPressedEvent(int keyCode)
                : m_keycode(keyCode) {};

        /**
         * @brief Type of this event
         */
        EventTypes GetEventType() override {
            return EventTypes::KeyPressed;
        }

        /**
         * @brief Prints the name of this event
         */
        void PrintEventName() override {
            PRINTMSG("KeyPressedEvent: {}", m_keycode);
        }

        /**
         * @brief Predicate for whether the event has
         *        been fully handled
         */
        bool Handled() override {
            return this->EventFinised;
        }

        /**
         * @brief Keycode for the key that has been pressed
         * 
         * @return Keycode representing a keyboard key
         */
        unsigned int GetKeyCode() {
            return m_keycode;
        }

        /**
         * @brief Type of this event
         */
        static EventTypes s_GetEventType() {
            return EventTypes::KeyPressed;
        }

    private:
        unsigned int m_keycode;
    };

    /**
     * @brief Emitted when any key is released
     */
    class KeyReleasedEvent : public Event {
    public:

        /**
         * @brief Constructor - takes a keycode to identify the
         *        released key
         * 
         * @param keyCode Keycode representing the released key
         */
        KeyReleasedEvent(int keyCode)
                : m_keycode(keyCode) {};

        /**
         * @brief Type of this event
         */
        EventTypes GetEventType() override {
            return EventTypes::KeyReleased;
        }

        /**
         * @brief Prints the name of this event
         */
        void PrintEventName() override {
            PRINTMSG("KeyReleasedEvent: {}", m_keycode);
        }

        /**
         * @brief Predicate for whether the event has
         *        been fully handled
         */
        bool Handled() override {
            return this->EventFinised;
        }

        /**
         * @brief Keycode for the key that has been released
         * 
         * @return Keycode representing a keyboard key
         */
        unsigned int GetKeyCode() {
            return m_keycode;
        }

        /**
         * @brief Type of this event
         */
        static EventTypes s_GetEventType() {
            return EventTypes::KeyReleased;
        }

    private:
        unsigned int m_keycode;
    };
} // namespace Agate

#endif // AGATE_KEYEVENTS_H
