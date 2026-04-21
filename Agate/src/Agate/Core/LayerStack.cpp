#include "agpch.h"

#include "LayerStack.h"

Agate::LayerStack::~LayerStack() {
    for (auto& layer : m_layers) {
        layer->Detach();
    }
    m_layers.clear();
}

void Agate::LayerStack::AddLayer(std::shared_ptr<Layer> layer) {
    layer->Attach();
    m_layers.emplace(m_layers.begin() + m_amountOfLayers, layer);
    m_amountOfLayers++;
}

void Agate::LayerStack::RemoveLayer(std::shared_ptr<Layer> layer) {
    auto it = std::find(m_layers.begin(), m_layers.begin() + m_amountOfLayers, layer);
    if (it != m_layers.begin() + m_amountOfLayers) {
        layer->Detach();
        m_layers.erase(it);
        m_amountOfLayers--;
    }
}

void Agate::LayerStack::AddOverlay(std::shared_ptr<Layer> overlay) {
    overlay->Attach();
    m_layers.push_back(overlay);
}

void Agate::LayerStack::RemoveOverlay(std::shared_ptr<Layer> overlay) {
    auto it = std::find(m_layers.begin() + m_amountOfLayers, m_layers.end(), overlay);
    if (it != m_layers.end()) {
        overlay->Detach();
        m_layers.erase(it);
    }
}
