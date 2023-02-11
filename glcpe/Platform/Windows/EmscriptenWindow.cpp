#include "EmscriptenWindow.h"

static bool s_GLFWInitialized = false;

Window* Window::create(const WindowProperties& properties)
{
    return new EmscriptenWindow(properties);
}

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
