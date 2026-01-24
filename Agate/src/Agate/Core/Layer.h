/**
 * @brief Include file for the Layer class. Layers are used to
 *        separate and order operations and events in the core
 *        loop
 */

#pragma once

#include "Agate/Events/Event.h"

namespace Agate {

    /**
     * @brief Base class for all layers
     */
    class Layer {
    public:

        /**
         * @brief Called immediately after being added to the 
         *        layer stack
         */
        virtual void Attach() {}

        /**
         * @brief Called immediately before being removed from
         *        the layer stack
         */
        virtual void Detach() {}

        /**
         * @brief Event handler for this layer
         * 
         * @param e Event to handle
         */
        virtual void OnEvent(Event &e) {}

        /**
         * @brief Called once every render frame
         */
        virtual void OnRender() {};

    private:
        bool m_Enabled = true;
    };
}// namespace Agate
