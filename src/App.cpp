#include "App.h"

#include <SDL.h>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

bool App::initialize() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  SDL_WindowFlags window_flags =
      (SDL_WindowFlags)(SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_UTILITY);

  window = SDL_CreateWindow("Graphics Engine", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, 1080, 720, window_flags);

  if (window == nullptr) {
    std::cerr << "Window could not be created! SDL Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

  if (renderer == nullptr) {
    std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO &io = ImGui::GetIO();

  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImGui::StyleColorsDark();
  // ImGui::StyleColorsLight();

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer2_Init(renderer);

  return true;
}

bool trisetn = true;

void App::update() {

  ImGui_ImplSDLRenderer2_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();

  {

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);      // Position
    ImGui::SetNextWindowSize(ImVec2(360, 720), ImGuiCond_Once); // Size
    ImGui::Begin("Fixed Window", NULL,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    if (ImGui::Button("Quit?")) {
      quit = true;
    }
    if (ImGui::Button("Quit Demo?")) {
      trisetn = !trisetn;
    }
    ImGui::End();
  }
  {
    if (trisetn) {
      ImGui::ShowDemoWindow(&trisetn);
    }
  }
}

void App::render() {

  ImGuiIO &io = ImGui::GetIO();
  ImGui::Render();
  SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x,
                     io.DisplayFramebufferScale.y);
  SDL_SetRenderDrawColor(
      renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255),
      (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
  SDL_RenderClear(renderer);
  ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

  // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  // SDL_RenderClear(renderer);
  //
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  // rendering stuff
  SDL_RenderPresent(renderer);
}

void App::close() {
  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  std::cout << "SuccessFully closed the application" << std::endl;
}

int App::RunEngine(App engine) {
  if (!engine.initialize()) {
    std::cerr << "Failed to initialize!" << std::endl;
    return 1;
  } else {
    std::cout << "SuccessFully initialised" << std::endl;
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
