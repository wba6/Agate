#include "agpch.h"

#include "LayerStack.h"

Agate::LayerStack::~LayerStack() {
    for (size_t i{0}; i < m_layers.size(); i++) {
        m_layers.at(i)->Detach();
        m_layers.erase(m_layers.begin() + i);
    }
}

void Agate::LayerStack::AddLayer(std::shared_ptr<Layer> layer) {
    layer->Attach();
    m_layers.emplace(m_layers.begin() + m_amountOfLayers, std::move(layer));
    m_amountOfLayers++;
}

void Agate::LayerStack::RemoveLayer(const std::shared_ptr<Layer> &layer) {
    for (size_t i{0}; i < m_layers.size(); i++) {
        if (layer == m_layers.at(i)) {
            layer->Detach();
            m_layers.erase(m_layers.begin() + i);
            break;
        }
    }
}

void Agate::LayerStack::AddOverlay(std::shared_ptr<Layer> overlay) {
    overlay->Attach();
    m_layers.push_back(std::move(overlay));
}

void Agate::LayerStack::RemoveOverlay(const std::shared_ptr<Layer> &overlay) {
    for (size_t i{m_layers.size()}; i >= 0; i--) {
        if (overlay == m_layers.at(i)) {
            overlay->Detach();
            m_layers.erase(m_layers.begin() + (m_layers.size() - i));
            break;
        }
    }
}
