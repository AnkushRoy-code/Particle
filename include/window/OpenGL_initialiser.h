#pragma once

#include <glad/glad.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>

#include "shader.h"

class openGLManager
{
  public:
    void initialise(SDL_Window *window, SDL_GLContext glContext);
    void close(SDL_GLContext glContext);

  private:
    Shader m_shader;
};
