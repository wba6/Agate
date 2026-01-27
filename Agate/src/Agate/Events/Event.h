/**
 * @brief Include file for base event classes and types
 */

#ifndef AGATE_EVENT_H
#define AGATE_EVENT_H

#include "agpch.h"

#include "Agate/Core/Core.h"
#include "Agate/Core/Logger.h"

namespace Agate {

    /**
     * @brief Built-in event types for the engine
     */
    enum class API EventTypes {
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        KeyPressed,
        KeyReleased,
        WindowResized,
        WindowClose

    };

    /**
     * @brief Base virtual class for engine events. 
     */
    class API Event {
        friend class EventNotifier;

    public:
        Event()
                : EventFinised(false) {}

        /**
         * @brief Type of this event
         */
        virtual EventTypes GetEventType() = 0;

        /**
         * @brief Prints the name of this event
         */
        virtual void PrintEventName() = 0;

        /**
         * @brief Predicate for whether the event has
         *        been fully handled
         */
        virtual bool Handled() = 0;

    protected:
        bool EventFinised;
    };

    /**
     * @brief Wrapper for event handlers. Consumes a generic
     *        `Event` and narrows it to a specialization of
     *        `Event` if possible to bind it to a callback
     *        that is then invoked
     */
    class API EventNotifier {
        template<typename T>
        using EventFn = std::function<bool(T &)>;

    public:

        /**
         * @brief Constructor; Creates a notifier for an event
         * 
         * @param e Event to handle
         */
        explicit EventNotifier(Event &e)
                : m_Event(e) {};

        /**
         * @brief Template that conditionally handles the underlying
         *        event if its event type matches that of the template
         *        argument
         * 
         * @param ev Handler for the event, given it is of the
         *           appropriate type
         * 
         * @return Whether the event has been handled by this invocation
         * @retval true The event has been handled
         * @retval false The event has not been handled
         */
        template<typename T>
        bool NotifyEvent(EventFn<T> ev) {
            if (m_Event.GetEventType() == T::s_GetEventType()) {
                m_Event.EventFinised = ev(*(T *) &m_Event);
                return true;
            }
            return false;
        }

    private:
        Event &m_Event;
    };

}// namespace Agate

#endif // AGATE_EVENT_H
