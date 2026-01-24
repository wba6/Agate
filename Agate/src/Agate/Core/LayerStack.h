#pragma once

#include "agpch.h"

#include "Layer.h"

namespace Agate {
    class LayerStack {
        friend class EntryPoint;

    public:
        LayerStack() = default;

        ~LayerStack();

        /**
         * Adds layer to the end of the layer stack but before overlay layers
         * @param layer
         */
        virtual void AddLayer(std::unique_ptr<Layer> layer);

        virtual void RemoveLayer(std::unique_ptr<Layer> layer);

        /**
         * adds an overlay layer, overlay layers are the last to be rendered
         * @param overlay
         */
        virtual void AddOverlay(std::unique_ptr<Layer> overlay);

        virtual void RemoveOverlay(std::unique_ptr<Layer> overlay);

    private:
        std::vector<std::unique_ptr<Layer>> m_layers;
        unsigned int m_amountOfLayers = 0;
    };
}// namespace Agate
