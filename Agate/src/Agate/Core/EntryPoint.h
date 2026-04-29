/**
 * @brief Include file for the EntryPoint class and CreateEntryPoint
 *        free function stub. Consuming applications should start here
 */

#ifndef AGATE_ENTRYPOINT_H
#define AGATE_ENTRYPOINT_H

#include "Agate/Events/ApplicationEvents.h"
#include "Agate/Events/Event.h"
#include "Agate/Window/Window.h"
#include "Core.h"
#include "LayerStack.h"
#include <atomic>

namespace Agate {

    /**
     * @brief Manages the layer stack, windowing and
     *        event systems while running the core loop
     *        for the engine
     */
    class API EntryPoint {
    public:
        EntryPoint();

        virtual ~EntryPoint();

        /**
         * @brief Begins the core render loop
         */
        void Run();

        /**
         * @brief Passes an event down the layer stack for
         *        each layer to respond to, until the event
         *        is tagged as handled
         * 
         * @param e Event to pass
         */
        void OnEvent(Event &e);

        /**
         * @brief Special event handler for WindowCloseEvent
         * 
         * @param e Triggering event
         * 
         * @return True
         */
        bool OnWindowClose(WindowCloseEvent &e);

        /**
         * @brief Special event handler for WindowResizedEvent
         * 
         * @param e Triggering event
         * 
         * @return False
         */
        bool OnWindowResized(WindowResizedEvent &e);

        /**
         * @brief Inserts a layer in front of the first overlay
         *        layer in the stack
         * 
         * @param layer Layer to insert
         */
        void EmplaceLayer(std::shared_ptr<Layer> layer);

        /**
         * @brief Removes a layer from the stack
         * 
         * @param layer Layer to remove
         */
        void RemoveLayer(std::shared_ptr<Layer> layer);

        /**
         * @brief Appends an overlay layer to the end of the
         *        stack
         * 
         * @param overlay Layer to append
         */
        void EmplaceOverlay(std::shared_ptr<Layer> overlay);

        /**
         * @brief Removes an overlay layer from the stack
         * 
         * @param overlay Layer to remove
         */
        void RemoveOverlay(std::shared_ptr<Layer> overlay);

        /**
         * @brief Time elapsed rendering the most recent frame
         *        in seconds
         * 
         * @return Number of seconds that have elapsed
         */
        float GetDeltaTime();

        /**
         * @brief Accessor for the main window managed by
         *        this instance
         * 
         * @return Shared pointer to the main window
         */
        std::shared_ptr<Agate::Window> GetWindow();

        /**
         * @brief Accessor to the singleton instance
         */
        static EntryPoint *&GetInstance();

    private:
        std::shared_ptr<Window> m_window;
        LayerStack m_layerStack;
        std::atomic<bool> m_running;
        std::atomic<float> m_deltaTime;

    private:
        static EntryPoint *s_instance;
    };

    /**
     * @warning Intentionally undefined - Consuming
     * applications must define this function 
     * to instantiate an entry for the engine
     * to run.
     * 
     * @brief Instantiates an application for the
     * engine to run
     */
    EntryPoint *CreateEntryPoint();

}// namespace Agate

#endif // AGATE_ENTRYPOINT_H
