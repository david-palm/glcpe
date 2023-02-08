#define SDL_MAIN_HANDLED
#include <iostream>

#include "glad/glad.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#include <SDL.h>
#include <SDL_opengles2.h>
#else
#include <SDL2/sdl.h>
#endif

SDL_Window* window = nullptr;
bool closed = false;

void mainLoop()
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT) closed = true;
    }
}

int main()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not be initialized: " << SDL_GetError() << "\n";
        return -1;
    }
    else
    {
        std::cout << "SDL successfully initialized!\n";
    }

    window = SDL_CreateWindow("GLCPE Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    SDL_GLContext context = SDL_GL_CreateContext(window);
    gladLoadGLES2Loader(SDL_GL_GetProcAddress);
    std::cout << "Test" << std::endl;

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainLoop, 0, true);
#else
    while(!closed)
    {
        mainLoop();
    }
#endif
    return 0;
}