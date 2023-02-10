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


void WindowsWindow::setVSync(bool enabled) {

}
bool WindowsWindow::isVSync() const
{
    return true;
}

void WindowsWindow::shutdown()
{
    SDL_DestroyWindow(m_Window);
}

void WindowsWindow::onUpdate() {
#ifndef __EMSCRIPTEN__
    SDL_GL_SwapWindow(m_Window);
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {

    }
#endif
}

void WindowsWindow::init(const WindowProperties& properties)
{
    m_WindowData.title = properties.title;
    m_WindowData.width = properties.width;
    m_WindowData.height = properties.height;

    m_WindowData.title = properties.title;
    m_WindowData.width = properties.width;
    m_WindowData.height = properties.height;
#ifndef __EMSCRIPTEN__
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
#else
    if(!s_GLFWInitialized)
    {
        int success = glfwInit();
        if(!success) {
            std::cerr << "Failed to initialize GLFW window" << std::endl;
            glfwTerminate();
        }
        s_GLFWInitialized = true;
    }
    m_Window = glfwCreateWindow(properties.width, properties.height, properties.title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_WindowData);
#endif
    setVSync(true);

    // Setting callbacks
#ifdef __EMSCRIPTEN__
    //EMSCRIPTEN callbacks
    EMSCRIPTEN_RESULT ret = emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, &m_WindowData, 1, [](int eventType, const EmscriptenKeyboardEvent *e, void *userData)
    {
        std::string keyCodeHtml(e->code);
        int keyCode = e->charCode;

        WindowData& windowData = *(WindowData*)userData;

        KeyDownEvent event(keyCode, e->repeat);
        windowData.eventCallback(event);

        return 0;
    });
    ret = emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, &m_WindowData, 1, [](int eventType, const EmscriptenKeyboardEvent *e, void *userData)
    {
        std::string keyCodeHtml(e->code);
        int keyCode = e->charCode;

        WindowData& windowData = *(WindowData*)userData;

        KeyUpEvent event(keyCode);
        windowData.eventCallback(event);
        return 0;
    });

    ret = emscripten_set_mousedown_callback("#canvas", &m_WindowData, 1, [](int eventType, const EmscriptenMouseEvent *e, void *userData)
    {
        WindowData& windowData = *(WindowData*)userData;

        MouseDownEvent event(e->button);
        windowData.eventCallback(event);
        return 0;
    });
    ret = emscripten_set_mouseup_callback("#canvas", &m_WindowData, 1, [](int eventType, const EmscriptenMouseEvent *e, void *userData)
    {
        WindowData& windowData = *(WindowData*)userData;

        MouseUpEvent event(e->button);
        windowData.eventCallback(event);
        return 0;
    });
    ret = emscripten_set_mousemove_callback("#canvas", &m_WindowData, 1, [](int eventType, const EmscriptenMouseEvent *e, void *userData)
    {
        WindowData& windowData = *(WindowData*)userData;

        float x = ((float) e->targetX / windowData.width) * 2.0f - 1.0f;
        float y = ((float) e->targetY / windowData.height) * 2.0f - 1.0f;

        MouseMoveEvent event(x, y);
        windowData.eventCallback(event);
        return 0;
    });
#endif


    SDL_AddEventWatch(reinterpret_cast<SDL_EventFilter>(sdlWindowCloseCallback), m_Window);
    SDL_AddEventWatch(reinterpret_cast<SDL_EventFilter>(sdlWindowResizeCallback), m_Window);
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

