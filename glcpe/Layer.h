#pragma once

#include "Events/Event.h"

class Layer
{
public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer();

    virtual void onAttach() {}
    virtual void onDetach() {}
    virtual void onUpdate() {}
    virtual void onEvent(Event& event) {}

    inline const std::string& getName() const { return m_Name; }
protected:
    std::string m_Name;
};