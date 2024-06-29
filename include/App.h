#pragma once

#include <SDL.h>

#include "imgui.h"

#include "SDLstuff.h"
#include "UI.h"
#include "simulation.h"

class App {
private:
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  UI ui;
  SDLStuff sdlStuff;
  Simulation simulation;

public:
  App() : window(nullptr), renderer(nullptr), simulation(720, 720) {}
  bool quit = false;

public:
  bool initialize();
  void update();
  void render();
  void close();
  int RunEngine(App engine);
};
