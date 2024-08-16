// this is the main application file

#pragma once

#include "SDLstuff.h"  // for making window/renderer
#include "UI.h"  // all the ui stuff. This also includes the particle class for particle stuff.

#include <SDL.h>

class App
{
  private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDLStuff sdlStuff;
    UI ui;

    bool quit = false;

  public:
    App() : window(nullptr), renderer(nullptr) {}

  public:
    int RunEngine(App engine);

  private:
    bool initialize();
    void update(float Scale, float offSetX, float offSetY);
    void processEvents(SDL_Event &event,
                       float &scale,
                       bool &middleMouseButtonPressed,
                       float &mouseStartPanX,
                       float &mouseStartPanY,
                       float &offsetX,
                       float &offsetY,
                       float &offsetEndX,
                       float &offsetEndY,
                       bool &quit);
    void adjustScale(const SDL_Event &event, float &scale);
    void handleMouseButtonDown(const SDL_Event &event,
                               bool &middleMouseButtonPressed,
                               float &mouseStartPanX,
                               float &mouseStartPanY,
                               float scale);
    void handleMouseButtonUp(const SDL_Event &event,
                             bool &middleMouseButtonPressed,
                             float &offsetX,
                             float &offsetY,
                             float &offsetEndX,
                             float &offsetEndY);
    void handleKeyDown(const SDL_Event &event,
                       float &scale,
                       float &offsetX,
                       float &offsetY,
                       float &offsetEndX,
                       float &offsetEndY);
    void handleMouseMotion(bool middleMouseButtonPressed,
                           float scale,
                           float mouseStartPanX,
                           float mouseStartPanY,
                           float &offsetX,
                           float &offsetY,
                           float &offsetEndX,
                           float &offsetEndY);
    void clampScale(float &scale);
    void finalizeFrame();
    void render();
    void close();
    void Quit() { quit = true; }
};
