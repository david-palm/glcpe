#include "EmscriptenWindow.h"

static bool s_GLFWInitialized = false;

#ifdef __EMSCRIPTEN__
Window* Window::create(const WindowProperties& properties)
{
    return new EmscriptenWindow(properties);
}
#endif

EmscriptenWindow::EmscriptenWindow(const WindowProperties& properties)
{
    init(properties);
}

EmscriptenWindow::~EmscriptenWindow()
{

}

void EmscriptenWindow::setVSync(bool enabled)
{
    if(enabled)
    {
#ifdef __EMSCRIPTEN__
        glfwSwapInterval(1);
#endif
    }
    else
    {
#ifdef __EMSCRIPTEN__
        glfwSwapInterval(0);
#endif
    }
    m_WindowData.vSync = enabled;
}
bool EmscriptenWindow::isVSync() const
{
    return true;
}

void EmscriptenWindow::shutdown()
{
    //Emscripten does not need a shutdown function
}

void EmscriptenWindow::onUpdate()
{
    //Emscripten does not need an update function
}

void EmscriptenWindow::init(const WindowProperties& properties)
{
    m_WindowData.title = properties.title;
    m_WindowData.width = properties.width;
    m_WindowData.height = properties.height;

    m_WindowData.title = properties.title;
    m_WindowData.width = properties.width;
    m_WindowData.height = properties.height;

#ifdef __EMSCRIPTEN__
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

    setVSync(true);

    // Setting callbacks

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
}

