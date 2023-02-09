#pragma once

#include <iostream>

#include "glad/glad.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#include <SDL.h>
#include <SDL_opengles2.h>
#else
#include <SDL2/sdl.h>
#include <memory>

#endif

class Application
{
public:
    Application();
    ~Application();

    static Application& get() { return *s_Instance; }
    //Emscripten limitation: MainLoop needs to be separate function
    void runLoop();

    //void onEvent(Event& event);
private:
    void run();
#ifndef __EMSCRIPTEN__
    //bool onWindowClose(WindowCloseEvent& event);
    //bool onWindowResize(WindowResizeEvent& event);
#endif
    //bool onKeyDown(KeyDownEvent& event);
    //bool onKeyUp(KeyUpEvent& event);

    //bool onMouseDown(MouseDownEvent& event);
    //bool onMouseUp(MouseUpEvent& event);
    //bool onMouseMove(MouseMoveEvent& event);

    //void pushLayer(Layer* layer);
    //void pushOverlay(Layer* layer);
private:
    static Application* s_Instance;
    bool m_Running = false;
    SDL_Window* m_Window;
    //std::unique_ptr<Window> m_Window;
    //LayerStack m_LayerStack;
};



