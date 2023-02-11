#pragma once

#include <SDL2/SDL.h>
#include<map>

#include "../../Events/WindowEvent.h"
#include "../../Events/KeyEvent.h"
#include "../../Events/MouseEvent.h"

#include "../../Window.h"

struct WindowData
{
    using EventCallbackFunction = std::function<void(Event&)>;
    std::string title;
    unsigned int width, height;
    bool vSync;

    EventCallbackFunction eventCallback;
};

class SDLWindow : public Window
{
public:
    SDLWindow(const WindowProperties& properties);
    virtual ~SDLWindow();

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
    WindowData m_WindowData;
};

//Callback functions
static int sdlWindowCloseCallback(void* data, SDL_Event* sdlEvent);
static int sdlWindowResizeCallback(void* data, SDL_Event* sdlEvent);

static int sdlKeyDownCallback(void* data, SDL_Event* sdlEvent);
static int sdlKeyUpCallback(void* data, SDL_Event* sdlEvent);

static int sdlMouseDownCallback(void* data, SDL_Event* sdlEvent);
static int sdlMouseUpCallback(void* data, SDL_Event* sdlEvent);
static int sdlMouseMoveCallback(void* data, SDL_Event* sdlEvent);