#include "SDLWindow.h"

#ifndef __EMSCRIPTEN__
Window* Window::create(const WindowProperties& properties)
{
    return new SDLWindow(properties);
}
#endif

SDLWindow::SDLWindow(const WindowProperties& properties)
{
    init(properties);
}

SDLWindow::~SDLWindow()
{

}


void SDLWindow::setVSync(bool enabled) {

}
bool SDLWindow::isVSync() const
{
    return true;
}

void SDLWindow::shutdown()
{
    SDL_DestroyWindow(m_Window);
}

void SDLWindow::onUpdate() {
    SDL_GL_SwapWindow(m_Window);
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {

    }
}

void SDLWindow::init(const WindowProperties& properties)
{
    m_WindowData.title = properties.title;
    m_WindowData.width = properties.width;
    m_WindowData.height = properties.height;

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
    m_Window = SDL_CreateWindow("GLCPE Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_WindowData.width, m_WindowData.height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GL_CreateContext(m_Window);
    SDL_SetWindowData(m_Window, "WindowData", &m_WindowData);

    setVSync(true);

    SDL_AddEventWatch(reinterpret_cast<SDL_EventFilter>(sdlWindowCloseCallback), m_Window);
    SDL_AddEventWatch(reinterpret_cast<SDL_EventFilter>(sdlWindowResizeCallback), m_Window);

    SDL_AddEventWatch(reinterpret_cast<SDL_EventFilter>(sdlKeyDownCallback), m_Window);
    SDL_AddEventWatch(reinterpret_cast<SDL_EventFilter>(sdlKeyUpCallback), m_Window);

    SDL_AddEventWatch(reinterpret_cast<SDL_EventFilter>(sdlMouseDownCallback), m_Window);
    SDL_AddEventWatch(reinterpret_cast<SDL_EventFilter>(sdlMouseUpCallback), m_Window);
    SDL_AddEventWatch(reinterpret_cast<SDL_EventFilter>(sdlMouseMoveCallback), m_Window);
}


static int sdlWindowCloseCallback(void* data, SDL_Event* sdlEvent)
{
   if(sdlEvent->type == SDL_QUIT || (sdlEvent->type == SDL_WINDOWEVENT && sdlEvent->window.event == SDL_WINDOWEVENT_CLOSE))
   {
       SDL_Window* window = (SDL_Window*)data;
       WindowData &windowData = *(WindowData *) SDL_GetWindowData(window, "WindowData");;

       WindowCloseEvent event;
       windowData.eventCallback(event);
   }
   return 1;
}

static int sdlWindowResizeCallback(void* data, SDL_Event* sdlEvent)
{
    if(sdlEvent->type == SDL_WINDOWEVENT && sdlEvent->window.event == SDL_WINDOWEVENT_RESIZED)
    {
        SDL_Window* window = (SDL_Window*)data;
        WindowData &windowData = *(WindowData *) SDL_GetWindowData(window, "WindowData");
        int width, height;
        SDL_GetWindowSize(window, &width, &height);
        windowData.width = width;
        windowData.height = height;

        WindowResizeEvent event(width, height);
        windowData.eventCallback(event);
    }
    return 1;
}

static int sdlKeyDownCallback(void* data, SDL_Event* sdlEvent)
{
    if(sdlEvent->type == SDL_KEYDOWN)
    {
        SDL_Window* window = (SDL_Window*)data;
        WindowData &windowData = *(WindowData *) SDL_GetWindowData(window, "WindowData");
        KeyDownEvent event(sdlEvent->key.keysym.sym, sdlEvent->key.repeat);
        windowData.eventCallback(event);
    }
    return 1;
}

static int sdlKeyUpCallback(void* data, SDL_Event* sdlEvent)
{
    if(sdlEvent->type == SDL_KEYUP)
    {
        SDL_Window* window = (SDL_Window*)data;
        WindowData &windowData = *(WindowData *) SDL_GetWindowData(window, "WindowData");
        KeyUpEvent event(sdlEvent->key.keysym.sym);
        windowData.eventCallback(event);
    }
    return 1;
}

static int sdlMouseDownCallback(void* data, SDL_Event* sdlEvent)
{
    if(sdlEvent->type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Window* window = (SDL_Window*)data;
        WindowData &windowData = *(WindowData *) SDL_GetWindowData(window, "WindowData");

        MouseDownEvent event(sdlEvent->button.button);
        windowData.eventCallback(event);
    }
    return 1;
}

static int sdlMouseUpCallback(void* data, SDL_Event* sdlEvent)
{
    if(sdlEvent->type == SDL_MOUSEBUTTONUP)
    {
        SDL_Window* window = (SDL_Window*)data;
        WindowData &windowData = *(WindowData *) SDL_GetWindowData(window, "WindowData");

        MouseUpEvent event(sdlEvent->button.button);
        windowData.eventCallback(event);
    }
    return 1;
}

static int sdlMouseMoveCallback(void* data, SDL_Event* sdlEvent)
{
    if(sdlEvent->type == SDL_MOUSEMOTION)
    {
        SDL_Window* window = (SDL_Window*)data;
        WindowData &windowData = *(WindowData *) SDL_GetWindowData(window, "WindowData");

        float x = (float) (sdlEvent->motion.x / (double) windowData.width) * 2.0 - 1.0;
        float y = (float) (sdlEvent->motion.y / (double) windowData.height) * 2.0 - 1.0;

        MouseMoveEvent event(x, y);
        windowData.eventCallback(event);
    }
    return 1;
}



