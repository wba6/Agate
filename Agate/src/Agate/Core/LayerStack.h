/**
 * @brief Include file for the LayerStack class. Used by the
 *        core loop to organize layers
 */

#ifndef AGATE_LAYERSTACK_H
#define AGATE_LAYERSTACK_H

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
        virtual void AddLayer(std::shared_ptr<Layer> layer);

        /**
         * @brief Removes a layer from the stack
         * 
         * @param layer Layer to remove
         */
        virtual void RemoveLayer(std::shared_ptr<Layer> layer);

        /**
         * @brief Adds an overlay layer, overlay layers are the last to be rendered
         * 
         * @param overlay Layer to add
         */
        virtual void AddOverlay(std::shared_ptr<Layer> overlay);

        /**
         * @brief Removes an overlay layer from the stack
         * 
         * @param overlay Layer to remove
         */
        virtual void RemoveOverlay(std::shared_ptr<Layer> overlay);

    private:
        std::vector<std::shared_ptr<Layer>> m_layers;
        unsigned int m_amountOfLayers = 0;
    };
}// namespace Agate

#endif // AGATE_LAYERSTACK_H
