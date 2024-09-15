// this is the main application file

#pragma once

#include <iostream>
#include <glad/glad.h>
#include <SDL.h>

#include "gui/UI.h"  // all the ui stuff. This also includes the particle class for particle stuff.
#include "window/Window.h"  // for making window/renderer
#include "window/input.h"

class App
{
  private:
    SDL_Window *m_window;
    SDL_GLContext m_glContext;

    WindowManager m_windowManager;
    UI m_UI;
    inputHandler m_inputHandler;

    bool m_quit = false;
    SDL_Event event;

  public:
    App() : m_window(nullptr), m_glContext(nullptr) {}

  public:
    int RunEngine(App engine);

  private:
    bool initialize();
    void update(float Scale, float offSetX, float offSetY);
    void render();
    void close();
    void Quit() { m_quit = true; }

    void clampScale(float &scale);
    void finalizeFrame();
};
