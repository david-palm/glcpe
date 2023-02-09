#include "Application.h"

Application::Application()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not be initialized: " << SDL_GetError() << "\n";
    }
    else
    {
        std::cout << "SDL successfully initialized!\n";
    }

    m_Window = SDL_CreateWindow("GLCPE Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    SDL_GLContext context = SDL_GL_CreateContext(m_Window);

    // Loading OpenGL ES2 pointers with glad and ending program if failing to do so
    if (!gladLoadGLES2Loader(SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }

    m_Running = true;
#ifndef __EMSCRIPTEN__
    run();
#endif
}

Application::~Application()
{}

void Application::runLoop()
{
    std::cout << "Loop test\n";
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(m_Window);
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT) m_Running = false;
    }
}
void Application::run()
{
    while(m_Running)
    {
        runLoop();
    }
}
