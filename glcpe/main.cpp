#define SDL_MAIN_HANDLED
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <Emscripten.h>
#endif
#include "Application.h"

Application* application;


int main()
{
    application = new Application();
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainLoop, 0, true);
#endif
    std::cout << "Test2";
    delete application;
    return 0;
}

void mainLoop()
{
    application->runLoop();
}
