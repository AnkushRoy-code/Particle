#include "App.h"
#include "SDLstuff.h"
#include "UI.h"

#include <SDL.h>
#include <iostream>

#include "imgui_impl_sdl2.h"

bool App::initialize() {

  sdlStuff.initialise(window, renderer);

  if (window == nullptr) {
    std::cerr << "Window could not be created! SDL Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  if (renderer == nullptr) {
    std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  ui.initialize(window, renderer);
  // IDK how to check if imgui was successfully initialised.
  return true;
}

// These are for deltaTime
Uint64 currentTick = SDL_GetPerformanceFrequency();
Uint64 lastTick = 0;
double deltaTime = 0;

// These are for capping fps because my monitor doesn't even support more
// than 60.
const int FPS = 60;
const int frameDelay = 1000 / FPS;
Uint32 frameStart;
int frameTime;

void calcDeltatime() {
  lastTick = currentTick;
  currentTick = SDL_GetPerformanceCounter();
  deltaTime = (double)((currentTick - lastTick) * 1000 /
                       (double)SDL_GetPerformanceFrequency());
}

void App::update() {
  quit = ui.setup();
  ui.update(renderer, deltaTime);

  // other things go here
}

void App::render() { SDL_RenderPresent(renderer); }

void App::close() {
  ui.close();
  sdlStuff.close(window, renderer);
}

int App::RunEngine(App Engine) {
  if (!Engine.initialize()) {
    std::cerr << "Failed to initialize!" << std::endl;
    return 1;
  }

  SDL_Event event;

  while (!Engine.quit) {
    frameStart = SDL_GetTicks();
    calcDeltatime();

    while (SDL_PollEvent(&event) != 0) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT) {
        Engine.quit = true;
      }
    }

    Engine.update();

    Engine.render();
  }

  frameTime = SDL_GetTicks() - frameStart;
  if (frameDelay > frameTime) {
    SDL_Delay(frameDelay - frameTime);
  }

  Engine.close();

  if (Engine.window != nullptr) {
    std::cout << "wtf W";
  }
  if (Engine.renderer != nullptr) {
    std::cout << "wtf R";
  }

  return 0;
}
