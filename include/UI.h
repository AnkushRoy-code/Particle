#pragma once

#include <SDL.h>
#include <imgui.h>

class UI {

public:
  void initialize(SDL_Window *window, SDL_Renderer *renderer);
  bool update();
  void render(SDL_Renderer *Renderer);
  void close();

  int getRadius();

private:
  bool showDemoWindow = true;

  int radius = 3;
};
