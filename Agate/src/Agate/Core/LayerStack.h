#pragma once
#include "agpch.h"

#include "Layer.h"


namespace Agate
{
    class LayerStack {
        friend class EntryPoint;

    public:
        LayerStack() = default;
        ~LayerStack();

        /**
         * Adds layer to the end of the layer stack but before overlay layers
         * @param layer
         */
        virtual void AddLayer(Layer *layer);
        virtual void RemoveLayer(Layer *layer);
        /**
         * adds an overlay layer, overlay layers are the last to be rendered
         * @param overlay
         */
        virtual void AddOverlay(Layer *overlay);
        virtual void RemoveOverlay(Layer *overlay);

    private:
        std::vector<Layer *> m_layers;
        unsigned int m_amountOfLayers = 0;
    };
}// namespace Agate
