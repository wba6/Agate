#include "agpch.h"

#include "LayerStack.h"

Agate::LayerStack::~LayerStack()
{
    for (size_t i{0}; i < m_layers.size(); i++)
    {
        m_layers.at(i)->Detach();
        delete m_layers.at(i);
        m_layers.erase(m_layers.begin() + i);
    }
}

void Agate::LayerStack::AddLayer(Layer *layer)
{
    m_layers.emplace(m_layers.begin() + m_amountOfLayers, layer);
    m_amountOfLayers++;
    layer->Attach();
}

void Agate::LayerStack::RemoveLayer(Layer *layer)
{
    for (size_t i{0}; i < m_layers.size(); i++)
    {
        if (layer == m_layers.at(i))
        {
            layer->Detach();
            delete layer;
            m_layers.erase(m_layers.begin() + i);
        }
    }
}

void Agate::LayerStack::AddOverlay(Layer *overlay)
{
    m_layers.push_back(overlay);
    overlay->Attach();
}

void Agate::LayerStack::RemoveOverlay(Layer *overlay)
{
    for (size_t i{m_layers.size()}; i >= 0; i--)
    {
        if (overlay == m_layers.at(i))
        {
            overlay->Detach();
            delete overlay;
            m_layers.erase(m_layers.begin() + (m_layers.size() - i));
        }
    }
}
