#pragma once

#include "agpch.h"

#include "Layer.h"


namespace Agate {

    /**
     * @brief Holds an ordering of layers accessible only by the
     *        core loop and event system
     * 
     * @note See Agate::EntryPoint
     */
    class LayerStack {
        friend class EntryPoint;

    public:
        LayerStack() = default;

        ~LayerStack();

        /**
         * @brief Adds a layer to the end of the layer stack but before overlay layers
         * 
         * @param layer Layer to add
         */
        virtual void AddLayer(Layer *layer);

        /**
         * @brief Removes a layer from the stack
         * 
         * @param layer Layer to remove
         */
        virtual void RemoveLayer(Layer *layer);

        /**
         * @brief Adds an overlay layer, overlay layers are the last to be rendered
         * 
         * @param overlay Layer to add
         */
        virtual void AddOverlay(Layer *overlay);

        /**
         * @brief Removes an overlay layer from the stack
         * 
         * @param overlay Layer to remove
         */
        virtual void RemoveOverlay(Layer *overlay);

    private:
        std::vector<Layer *> m_layers;
        unsigned int m_amountOfLayers = 0;
    };
}// namespace Agate
