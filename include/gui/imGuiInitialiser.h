#pragma once

#include <SDL.h>
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>

#include "font.h"

class imGuiManager
{
  public:
    void initialise(SDL_Window *window, SDL_GLContext glContext);
    void setup();
    void close();
};
