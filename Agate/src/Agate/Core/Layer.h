/**
 * @brief Include file for the Layer class. Layers are used to
 *        separate and order operations and events in the core
 *        loop
 */

#ifndef AGATE_LAYER_H
#define AGATE_LAYER_H

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
        virtual void Attach() = 0; 

        /**
         * @brief Called immediately before being removed from
         *        the layer stack
         */
        virtual void Detach() = 0; 

        /**
         * @brief Event handler for this layer
         * 
         * @param e Event to handle
         */
        virtual void OnEvent(Event &e) = 0; 

        /**
         * @brief Called once every render frame
         */
        virtual void OnRender() = 0;

        /**
         * @brief Called once every game loop 
         */
        virtual void OnUpdate() = 0;



    private:
        bool m_Enabled = true;
    };
}// namespace Agate

#endif // AGATE_LAYER_H
