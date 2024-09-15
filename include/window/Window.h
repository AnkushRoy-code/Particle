#pragma once

#include <SDL.h>
#include <iostream>

#include "SDL_initialiser.h"
#include "OpenGL_initialiser.h"

class WindowManager
{
  public:
    void initialise(SDL_Window *&window, SDL_GLContext glContext);
    void close(SDL_Window *&window, SDL_GLContext glContext);

  private:
    SDL_Manager m_SDLManager;
    openGLManager m_openglManager;
};
