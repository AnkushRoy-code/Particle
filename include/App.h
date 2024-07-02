#pragma once

#include <SDL.h>

#include "SDLstuff.h"
#include "UI.h"

class App {
private:
  SDL_Window *window;
  SDL_Renderer *renderer;

  UI ui;
  SDLStuff sdlStuff;

  bool quit = false;

public:
  App() : window(nullptr), renderer(nullptr), ui(720, 720) {}

public:
  bool initialize();
  void update();
  void render();
  void close();
  void Quit() { quit = true; }
  int RunEngine(App engine);
};
