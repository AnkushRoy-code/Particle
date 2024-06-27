#pragma once

#include <SDL.h>
#include <imgui.h>

class UI {

public:
  void initialize(SDL_Window *window, SDL_Renderer *renderer);
  bool update();
  void close();

private:
  bool showDemoWindow = true;
};
