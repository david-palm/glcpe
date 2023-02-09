#pragma once

#include <sstream>
#include "Event.h"

class WindowCloseEvent : public Event
{
public:
    WindowCloseEvent() = default;

    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryWindow)
};

class WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(unsigned int width, unsigned int height)
            : m_Width(width), m_Height(height) {}

    unsigned int getWidth() const { return m_Width; }
    unsigned int getHeight() const { return m_Height; }

    std::string toString() const override
    {
        std::stringstream stringStream;
        stringStream << "WindowResizeEvent: " << m_Width << ", " << m_Height;
        return stringStream.str();
    }

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryWindow)
private:
    unsigned int m_Width;
    unsigned int m_Height;
};
