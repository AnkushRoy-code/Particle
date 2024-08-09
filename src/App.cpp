#include "App.h"

#include "SDLstuff.h"
#include "UI.h"
#include "imgui_impl_sdl2.h"

#include <SDL.h>
#include <iostream>

//---------------------------------------------------------------------------
//  Local Things
//---------------------------------------------------------------------------

// These are for deltaTime
Uint64 currentTick = SDL_GetPerformanceFrequency();
Uint64 lastTick    = 0;
double deltaTime   = 0;

// These are for capping fps because my monitor doesn't even support more
// than 60.
const int FPS        = 60;
const int frameDelay = 1000 / FPS;
Uint32 frameStart;
int frameTime;

void calcDeltatime()
{
  lastTick    = currentTick;
  currentTick = SDL_GetPerformanceCounter();
  deltaTime   = (double)((currentTick - lastTick) * 1000
                       / (double)SDL_GetPerformanceFrequency());
}

//---------------------------------------------------------------------------
// Implementation Of functions
//---------------------------------------------------------------------------
bool App::initialize()
{
  sdlStuff.initialise(window, renderer);

  if (window == nullptr)
  {
    std::cerr << "Window could not be created! SDL Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  if (renderer == nullptr)
  {
    std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  int h, w;
  SDL_GetWindowSize(window, &w, &h);

  ui.initialize(window, renderer, w, h);
  // IDK how to check if imgui was successfully initialised.
  return true;
}

void App::update(float Scale, float offSetX, float offSetY)
{
  ui.setup();
  ui.update(renderer, deltaTime, Scale, offSetX, offSetY);

  int h, w;
  SDL_GetWindowSize(window, &w, &h);

  ui.setSize(w, h);
}

void App::render() { SDL_RenderPresent(renderer); }

void App::close()
{
  ui.close();
  sdlStuff.close(window, renderer);
}

int App::RunEngine(App Engine)
{
  if (!Engine.initialize())
  {
    std::cerr << "Failed to initialize!" << std::endl;
    return 1;
  }

  float offsetX                 = 0.0f;
  float offsetY                 = 0.0f;
  float offsetEndX              = 0.0f;
  float offsetEndY              = 0.0f;
  float mouseStartPanX          = 0.0f;
  float mouseStartPanY          = 0.0f;
  float scale                   = 1.0f;
  bool middleMouseButtonPressed = false;
  SDL_Event event;

  while (!Engine.quit)
  {
    frameStart = SDL_GetTicks();
    calcDeltatime();

    while (SDL_PollEvent(&event) != 0)
    {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT) { Engine.quit = !Engine.quit; }
      else if (event.type == SDL_MOUSEWHEEL)
      {
        if (event.wheel.y > 0) { scale *= 1.05f; }
        else if (event.wheel.y < 0) { scale *= 0.95f; }
      }
      else if (event.type == SDL_MOUSEBUTTONDOWN)
      {
        if (event.button.button == SDL_BUTTON_MIDDLE)
        {
          middleMouseButtonPressed = true;
          int x, y;
          SDL_GetMouseState(&x, &y);

          mouseStartPanX = x / scale;
          mouseStartPanY = y / scale;
        }
      }
      else if (event.type == SDL_MOUSEBUTTONUP)
      {
        if (event.button.button == SDL_BUTTON_MIDDLE)
        {
          middleMouseButtonPressed = false;
          offsetEndX               = offsetX;
          offsetEndY               = offsetY;
        }
      }
      else if (event.type == SDL_KEYDOWN)
      {
        switch (event.key.keysym.sym)
        {
          case SDLK_m:
            offsetY    = 0.0f;
            offsetX    = 0.0f;
            offsetEndY = 0.0f;
            offsetEndX = 0.0f;
            break;

          case SDLK_z: scale = 1.0f; break;

          default: break;
        }
      }
    }

    if (middleMouseButtonPressed)
    {
      int x, y;
      SDL_GetMouseState(&x, &y);  // Get current mouse position

      offsetY = offsetEndY + ((y / scale) - mouseStartPanY);
      offsetX = offsetEndX + ((x / scale) - mouseStartPanX);
    }

    // cap scale value
    if (scale < 1.05f && scale > 0.95) { scale = 1; }
    else if (scale >= 5.0f) { scale = 5.0f; }
    else if (scale <= 0.5f) { scale = 0.5f; }

    Engine.update(scale, offsetX, offsetY);
    Engine.render();
  }

  frameTime = SDL_GetTicks() - frameStart;
  if (frameDelay > frameTime) { SDL_Delay(frameDelay - frameTime); }

  Engine.close();

  if (Engine.window != nullptr) { std::cout << "Window failed to close"; }
  if (Engine.renderer != nullptr) { std::cout << "Renderer failed to close"; }

  return 0;
}
