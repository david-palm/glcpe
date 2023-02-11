#pragma once

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#define GLFW_INCLUDE_ES3
#include "GLFW/glfw3.h"
#endif

#include "../../Window.h"

struct WindowData
{
    using EventCallbackFunction = std::function<void(Event&)>;
    std::string title;
    unsigned int width, height;
    bool vSync;

    EventCallbackFunction eventCallback;
};

class EmscriptenWindow : public Window
{
    virtual ~EmscriptenWindow();

    void onUpdate() override;
    inline unsigned int getWidth() const override { return m_WindowData.width; }
    inline unsigned int getHeight() const override { return m_WindowData.height; }
    inline void setEventCallback(const EventCallbackFunction& callback) override { m_WindowData.eventCallback = callback; }
    void setVSync(bool enabled) override;
    bool isVSync() const override;

public:
    EmscriptenWindow(const WindowProperties& properties);

private:
    virtual void init(const WindowProperties& properties);
    virtual void shutdown();

private:
#ifdef __EMSCRIPTEN__
    GLFWwindow* m_Window;
#endif
    WindowData m_WindowData;

};

