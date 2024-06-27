#include "UI.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include <SDL.h>

void UI::initialize(SDL_Window *window, SDL_Renderer *renderer) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();

  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImGui::StyleColorsDark();
  ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer2_Init(renderer);
}

bool UI::update() {

  ImGui_ImplSDLRenderer2_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();

  bool QUIT = false;

  {
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(360, 720), ImGuiCond_Once);

    ImGui::Begin("Control Panel", NULL,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    if (ImGui::Button("Quit?")) {
      QUIT = true;
    }

    if (ImGui::Button("Quit Demo?")) {
      showDemoWindow = !showDemoWindow;
    }

    ImGui::End();
  }

  {
    if (showDemoWindow) {
      ImGui::ShowDemoWindow(&showDemoWindow);
    }
  }

  return QUIT;
}

void UI::render(SDL_Renderer *Renderer) {
  ImGuiIO &io = ImGui::GetIO();
  ImGui::Render();
  SDL_RenderSetScale(Renderer, io.DisplayFramebufferScale.x,
                     io.DisplayFramebufferScale.y);
  SDL_SetRenderDrawColor(Renderer, 55, 55, 55, 255);
  SDL_RenderClear(Renderer);
  ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

void UI::close() {

  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();

  ImGui::DestroyContext();
}
