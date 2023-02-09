#pragma once

//#include "Events/Event.h"

#include <string>

struct WindowProperties
{
    std::string title;
    unsigned int width;
    unsigned int height;

    WindowProperties(const std::string& title = "GLWE", unsigned int width = 1280, unsigned int height = 720)
            : title(title), width(width), height(height)
    {}
};

class Window
{
public:
    //using EventCallbackFunction = std::function<void(Event&)>;

    virtual ~Window() {}

    virtual void onUpdate() = 0;
    virtual unsigned int getWidth() const = 0;
    virtual unsigned int getHeight() const = 0;

    //virtual void setEventCallback(const EventCallbackFunction& callback) = 0;
    virtual void setVSync(bool enabled) = 0;
    virtual bool isVSync() const = 0;
    static Window* create(const WindowProperties& properties = WindowProperties());

};