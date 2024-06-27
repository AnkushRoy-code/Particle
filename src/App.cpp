#include "App.h"

#include <SDL.h>
#include <SDL_render.h>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

bool App::initialize() {
  sdlStuff.initialise(window, renderer);
  ui.initialize(window, renderer);

  return true;
}

bool trisetn = true;

void App::update() {
  quit = ui.update();
  ui.render(renderer);
}

void App::render() { SDL_RenderPresent(renderer); }

void App::close() {
  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int App::RunEngine(App engine) {
  if (!engine.initialize()) {
    std::cerr << "Failed to initialize!" << std::endl;
    return 1;
  }
  SDL_Event event;

  while (!engine.quit) {
    while (SDL_PollEvent(&event) != 0) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT) {
        engine.quit = true;
      }
    }

    engine.update();
    engine.render();
  }

  engine.close();

  return 0;
}
