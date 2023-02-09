#pragma once

#include "glad/glad.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#include <SDL.h>
#include <SDL_opengles2.h>
#else
#include <SDL2/SDL.h>
#endif

#include <iostream>
#include <memory>

#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

#include "Window.h"
#include "Layer.h"
#include "LayerStack.h"

#include "Events/WindowEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

static std::string vertexShaderSourceTriangle = R"(#version 300 es
                                 layout (location = 0) in vec2 aPos;
                                 layout (location = 1) in vec4 aColor;
                                 out vec4 vColor;
                                 void main()
                                 {
                                    vColor = aColor;
                                    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
                                 })";
static std::string fragmentShaderSourceTriangle = R"(#version 300 es
                                   precision mediump float;
                                   out vec4 FragColor;
                                   in vec4 vColor;
                                   void main()
                                   {
                                        FragColor = vColor;
                                   })";

static std::string vertexShaderSourceSquare = R"(#version 300 es
                                 layout (location = 0) in vec2 aPos;
                                 void main()
                                 {
                                    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
                                 })";

static std::string fragmentShaderSourceSquare = R"(#version 300 es
                                   precision mediump float;
                                   out vec4 FragColor;
                                   void main()
                                   {
                                        FragColor = vec4(0.0f, 0.0f, 1.0f, 0.0f);
                                   })";

static std::string fragmentShaderSourceSquare_2 = R"(#version 300 es
                                   precision mediump float;
                                   out vec4 FragColor;
                                   void main()
                                   {
                                        FragColor = vec4(1.0f, 1.0f, 1.0f, 0.0f);
                                   })";


static std::unique_ptr<Shader> shaderTriangle;
static std::unique_ptr<Shader> shaderSquare;

static std::unique_ptr<VertexArray> vertexArrayTriangle;
static std::unique_ptr<VertexArray> vertexArraySquare;

class Application
{
public:
    Application();
    ~Application();

    static Application& get() { return *s_Instance; }
    void runLoop();

    void onEvent(Event& event);
private:
    void run();
#ifndef __EMSCRIPTEN__
    bool onWindowClose(WindowCloseEvent& event);
    bool onWindowResize(WindowResizeEvent& event);
#endif
    bool onKeyDown(KeyDownEvent& event);
    bool onKeyUp(KeyUpEvent& event);

    bool onMouseDown(MouseDownEvent& event);
    bool onMouseUp(MouseUpEvent& event);
    bool onMouseMove(MouseMoveEvent& event);

    void pushLayer(Layer* layer);
    void pushOverlay(Layer* layer);
private:
    static Application* s_Instance;
    bool m_Running = false;
    //SDL_Window* m_Window;
    std::unique_ptr<Window> m_Window;
    LayerStack m_LayerStack;
};



