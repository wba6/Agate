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

        virtual void AddLayer(Layer *layer);
        virtual void RemoveLayer(Layer *layer);
        virtual void AddOverlay(Layer *overlay);
        virtual void RemoveOverlay(Layer *overlay);

    private:
        std::vector<Layer *> m_layers;
        unsigned int m_amountOfLayers = 0;
    };
}// namespace Agate
