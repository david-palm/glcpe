#pragma once

#include <sstream>
#include "Event.h"

class MouseButtonEvent : public Event
{
public:
    int getMouseButton() const { return m_Button; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
protected:
    MouseButtonEvent(const int button)
        : m_Button(button) {}
    int m_Button;
};

class MouseDownEvent : public MouseButtonEvent
{
public:
    MouseDownEvent(const int button)
        : MouseButtonEvent(button) {}

    std::string toString() const override
    {
        std::stringstream stringStream;
        stringStream << "MouseDown Event: " << m_Button;
        return stringStream.str();
    };

    EVENT_CLASS_TYPE(MouseDown)
};

class MouseUpEvent : public MouseButtonEvent
{
public:
    MouseUpEvent(const int button)
            : MouseButtonEvent(button) {}

    std::string toString() const override
    {
        std::stringstream stringStream;
        stringStream << "MouseUp Event: " << m_Button;
        return stringStream.str();
    };

    EVENT_CLASS_TYPE(MouseUp)
};

class MouseMoveEvent : public Event
{
public:
    MouseMoveEvent(const float x, const float y)
        : m_X(x), m_Y(y) {}

    float getX() const { return m_X; }
    float getY() const { return m_Y; }

    std::string toString() const override
    {
        std::stringstream stringStream;
        stringStream << "MouseMove Event: " << m_X << ", " << m_Y;
        return stringStream.str();
    }

    EVENT_CLASS_TYPE(MouseMove)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
    float m_X;
    float m_Y;
};
