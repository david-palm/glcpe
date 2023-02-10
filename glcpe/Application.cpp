#include "Application.h"

#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)

class ExampleLayer : public Layer
{
public:
    ExampleLayer()
            : Layer("Example") {}

    void onUpdate() override
    {
        std::cout << "Updating Example Layer" << std::endl;
    }

    void onEvent(Event& event) override
    {
        std::cout << event.toString() << std::endl;
    }
};
Application::Application()
{
    pushLayer(new ExampleLayer());

    m_Window = std::unique_ptr<Window>(Window::create());
    m_Window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
#ifndef __EMSCRIPTEN__
    // Loading OpenGL ES2 pointers with glad and ending program if failing to do so
    if (!gladLoadGLES2Loader(SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }
#endif
    // Create triangle
    float verticesTriangle[18] = {
            -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,// left
            0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,// right
            0.0f, 0.5f,   0.0f, 0.0f, 1.0f, 1.0f// top
    };

    uint32_t indicesTriangle[3] = { 0, 1, 2 };

    std::shared_ptr<VertexBuffer> vertexBufferTriangle;
    std::shared_ptr<IndexBuffer> indexBufferTriangle;

    shaderTriangle.reset(new Shader(vertexShaderSourceTriangle, fragmentShaderSourceTriangle));
    vertexBufferTriangle.reset(VertexBuffer::create(verticesTriangle, sizeof(verticesTriangle)));
    indexBufferTriangle.reset(IndexBuffer::create(indicesTriangle, sizeof(indicesTriangle) / sizeof(uint32_t)));
    vertexArrayTriangle.reset(VertexArray::create());

    vertexArrayTriangle->bind();


    BufferLayout bufferLayoutTriangle =
            {
                    { ShaderDataType::Vec2, "aPosition" },
                    { ShaderDataType::Vec4, "aColor"}
            };
    vertexBufferTriangle->setLayout(bufferLayoutTriangle);
    vertexArrayTriangle->addVertexBuffer(vertexBufferTriangle);
    vertexArrayTriangle->setIndexBuffer(indexBufferTriangle);

    vertexBufferTriangle->unbind();

    float verticesSquare[24] = {
            -0.7f, -0.7f, // left
            -0.7f, 0.7f,  // right
            0.7f, -0.7f,  // top
            0.7f, 0.7f    // top
    };

    uint32_t indicesSquare[6] = { 0, 1, 2, 1, 2, 3 };

    std::shared_ptr<VertexBuffer> vertexBufferSquare;
    std::shared_ptr<IndexBuffer> indexBufferSquare;

    shaderSquare.reset(new Shader(vertexShaderSourceSquare, fragmentShaderSourceSquare));
    vertexBufferSquare.reset(VertexBuffer::create(verticesSquare, sizeof(verticesSquare)));
    indexBufferSquare.reset(IndexBuffer::create(indicesSquare, sizeof(indicesSquare) / sizeof(uint32_t)));
    vertexArraySquare.reset(VertexArray::create());

    vertexArraySquare->bind();

    BufferLayout bufferLayoutSquare =
            {
                    { ShaderDataType::Vec2, "aPosition" },
            };
    vertexBufferSquare->setLayout(bufferLayoutSquare);
    vertexArraySquare->addVertexBuffer(vertexBufferSquare);
    vertexArraySquare->setIndexBuffer(indexBufferSquare);

    vertexBufferSquare->unbind();

    glClearColor(1.0f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_Running = true;
    run();
    SDL_Quit();
}

Application::~Application()
{}

void Application::runLoop()
{
    /* Render here */
    glClearColor(1.0f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderSquare->bind();
    vertexArraySquare->bind();
    glDrawElements(GL_TRIANGLES, vertexArraySquare->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    shaderTriangle->bind();
    vertexArrayTriangle->bind();
    glDrawElements(GL_TRIANGLES, vertexArrayTriangle->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

    for(Layer* layer : m_LayerStack)
    {
        layer->onUpdate();
    }
#ifndef __EMSCRIPTEN__
    m_Window->onUpdate();
#endif
}
void Application::run()
{
#ifndef __EMSCRIPTEN__
    while(m_Running)
    {
        runLoop();
    }
#endif
}

void Application::onEvent(Event& event)
{
    EventDispatcher dispatcher(event);
#ifndef __EMSCRIPTEN__
    dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(onWindowClose));
    dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FUNCTION(onWindowResize));
#endif
    dispatcher.dispatch<KeyDownEvent>(BIND_EVENT_FUNCTION(onKeyDown));
    dispatcher.dispatch<KeyUpEvent>(BIND_EVENT_FUNCTION(onKeyUp));

    dispatcher.dispatch<MouseDownEvent>(BIND_EVENT_FUNCTION(onMouseDown));
    dispatcher.dispatch<MouseUpEvent>(BIND_EVENT_FUNCTION(onMouseUp));
    dispatcher.dispatch<MouseMoveEvent>(BIND_EVENT_FUNCTION(onMouseMove));

    for(auto iterator = m_LayerStack.end(); iterator != m_LayerStack.begin(); )
    {
        (*--iterator)->onEvent(event);
        if(event.m_Handled)
        {
            break;
        }
    }
}

#ifndef __EMSCRIPTEN__
bool Application::onWindowClose(WindowCloseEvent& event)
{
    m_Running = false;
    return true;
}
bool Application::onWindowResize(WindowResizeEvent& event)
{
    return true;
}
#endif

bool Application::onKeyDown(KeyDownEvent& event)
{
    return true;
}
bool Application::onKeyUp(KeyUpEvent& event)
{
    return true;
}

bool Application::onMouseDown(MouseDownEvent& event)
{
    return true;
}
bool Application::onMouseUp(MouseUpEvent& event)
{
    return true;
}
bool Application::onMouseMove(MouseMoveEvent& event)
{
    return true;
}

void Application::pushLayer(Layer* layer)
{
    m_LayerStack.pushLayer(layer);
}

void Application::pushOverlay(Layer* layer)
{
    m_LayerStack.pushOverlay(layer);
}
