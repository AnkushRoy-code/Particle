// this is the main application file

#pragma once

#include <SDL.h>

#include "SDLstuff.h" // for making window/renderer
#include "UI.h" // all the ui stuff. This also includes the particle class for particle stuff.

class App {
private:
  SDL_Window *window;
  SDL_Renderer *renderer;

  UI ui;
  SDLStuff sdlStuff;

  bool quit = false;

public:
  App() : window(nullptr), renderer(nullptr) {}

public:
  int RunEngine(App engine);

private:
  bool initialize();
  void update(float Scale, float offSetX, float offSetY);
  void render();
  void close();
  void Quit() { quit = true; }
};
