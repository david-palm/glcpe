#include "WindowsWindow.h"

#include "../../Events/WindowEvent.h"
#include "../../Events/KeyEvent.h"
#include "../../Events/MouseEvent.h"


static bool s_GLFWInitialized = false;

Window* Window::create(const WindowProperties& properties)
{
    return new WindowsWindow(properties);
}

WindowsWindow::WindowsWindow(const WindowProperties& properties)
{
    init(properties);
}

WindowsWindow::~WindowsWindow()
{

}

void WindowsWindow::init(const WindowProperties& properties)
{
    m_WindowData.title = properties.title;
    m_WindowData.width = properties.width;
    m_WindowData.height = properties.height;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not be initialized: " << SDL_GetError() << "\n";
    }
    else
    {
        std::cout << "SDL successfully initialized!\n";
    }

    m_Window = SDL_CreateWindow("GLCPE Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_WindowData.width, m_WindowData.height, SDL_WINDOW_OPENGL);
    SDL_GL_CreateContext(m_Window);
}
void WindowsWindow::setVSync(bool enabled)
{}
bool WindowsWindow::isVSync() const
{
    return true;
}

void WindowsWindow::shutdown()
{
    SDL_DestroyWindow(m_Window);
}

void WindowsWindow::onUpdate()
{
#ifndef __EMSCRIPTEN__
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            shutdown();
        }
    }
#endif
}
