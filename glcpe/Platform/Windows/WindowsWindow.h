#pragma once

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include<map>

#include "../../Window.h"

class WindowsWindow : public Window
{
public:
    WindowsWindow(const WindowProperties& properties);
    virtual ~WindowsWindow();

    void onUpdate() override;
    inline unsigned int getWidth() const override { return m_WindowData.width; }
    inline unsigned int getHeight() const override { return m_WindowData.height; }
    inline void setEventCallback(const EventCallbackFunction& callback) override { m_WindowData.eventCallback = callback; }
    void setVSync(bool enabled) override;
    bool isVSync() const override;
private:
    virtual void init(const WindowProperties& properties);
    virtual void shutdown();
private:
    SDL_Window* m_Window;

    struct WindowData
    {
        std::string title;
        unsigned int width, height;
        bool vSync;

        EventCallbackFunction eventCallback;
    };

    WindowData m_WindowData;
};
