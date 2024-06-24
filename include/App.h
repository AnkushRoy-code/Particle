#pragma once

#include <SDL.h>

#include "imgui.h"

class App {
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

public:
  App() : window(nullptr), renderer(nullptr) {}

  bool quit = false;
  bool initialize();
  void update();
  void render();
  void close();
  int RunEngine(App engine);
};
