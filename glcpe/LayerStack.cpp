#include "LayerStack.h"

LayerStack::LayerStack()
{
    m_LayerInsert = m_Layers.begin();
}

LayerStack::~LayerStack()
{
    for(Layer* layer : m_Layers)
        delete layer;
}

void LayerStack::pushLayer(Layer* layer)
{
    m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
}

void LayerStack::popLayer(Layer* layer)
{
    auto iterator = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if(iterator != m_Layers.end())
    {
        m_Layers.erase(iterator);
        m_LayerInsert--;
    }
}

void LayerStack::pushOverlay(Layer* overlay)
{
    m_Layers.emplace_back(overlay);
}

void LayerStack::popOverlay(Layer* overlay)
{
    auto iterator = std::find(m_Layers.begin(), m_Layers.end(), overlay);
    if(iterator != m_Layers.end())
    {
        m_Layers.erase(iterator);
    }
}