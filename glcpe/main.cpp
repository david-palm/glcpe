#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL2/sdl.h>

int main() {
    SDL_Window* window;
    SDL_INIT_EVERYTHING;

    window = SDL_CreateWindow("GLCPE Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    bool closed = false;
    while(!closed)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT) closed = true;
        }

    }
    return 0;
}
