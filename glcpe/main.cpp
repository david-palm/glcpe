#define SDL_MAIN_HANDLED
#include <iostream>

#include "Application.h"

Application* application;

void mainLoop()
{
    application->runLoop();
}

int main()
{
    application = new Application();
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainLoop, 0, true);
#endif
    return 0;
}
