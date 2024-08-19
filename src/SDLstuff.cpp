#include "SDLstuff.h"

#include <SDL.h>
#include <iostream>

void SDLStuff::initialise(SDL_Window *&window, SDL_Renderer *&renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError()
                  << std::endl;
        return;
    }

    SDL_WindowFlags window_flags =
        (SDL_WindowFlags)(SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_UTILITY
                          | SDL_WINDOW_RESIZABLE);

    window = SDL_CreateWindow("Graphics Engine", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, m_WIDTH, m_HEIGHT,
                              window_flags);

    if (window == nullptr)
    {
        std::cerr << "Window could not be created! SDL Error: "
                  << SDL_GetError() << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr)
    {
        std::cerr << "Renderer could not be created! SDL Error: "
                  << SDL_GetError() << std::endl;

        return;
    }
}
void SDLStuff::close(SDL_Window *&window, SDL_Renderer *&renderer)
{
    if (renderer != nullptr)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window != nullptr)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}
