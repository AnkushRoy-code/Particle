#pragma once

#include <SDL.h>

class SDLStuff
{
  public:
    void initialise(SDL_Window *&window, SDL_Renderer *&renderer);
    void close(SDL_Window *&window, SDL_Renderer *&renderer);

  private:
    const int WIDTH = 1080, HEIGHT = 720;
};
