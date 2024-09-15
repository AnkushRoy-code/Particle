#pragma once

#include <SDL.h>
#include <iostream>

class SDL_Manager
{
  public:
    void initialise(SDL_Window *&window, SDL_GLContext glContext);
    void close(SDL_Window *&window);

  private:
    const int m_WIDTH  = 1080;
    const int m_HEIGHT = 720;
};
