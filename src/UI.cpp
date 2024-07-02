#include "UI.h"
#include "color.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <SDL.h>
#include <ctime>
#include <random>

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

  ImGuiStyle &style = ImGui::GetStyle();

  // For some friendly looking buttons
  style.FrameRounding = 5.0f;
  style.GrabRounding = 12.0f;
  style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
  style.SeparatorTextAlign = ImVec2(0.5f, 0.5f);
  initializeParticle(100, 4);
}

static void HelpMarker(const char *desc) {
  ImGui::TextDisabled("(?)");
  if (ImGui::BeginItemTooltip()) {
    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
    ImGui::TextUnformatted(desc);
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();
  }
}

void UI::checkBool(int start, int end, const char *string) {
  if (numOfParticleColor >= end + 1) {
    ImGui::SliderFloat(string, &Force[start][end], -1, 1, 0,
                       ImGuiSliderFlags_AlwaysClamp);
  }
}

bool UI::setup() {
  ImGui_ImplSDLRenderer2_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();

  bool QUIT = false;
  auto guiWidgetFlags = ImGuiSliderFlags_AlwaysClamp;
  {

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(360, 720), ImGuiCond_Once);

    ImGui::Begin("Control Panel", NULL,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking);

    if (ImGui::Button("Quit?")) {
      QUIT = true;
    }

    ImGui::SeparatorText("Global variables");

    ImGui::SliderInt("Radius", &radius, 0, 10, 0, guiWidgetFlags);

    ImGui::Text("Particle Count");
    ImGui::PushID(1);
    ImGui::SliderInt(" ", &particleCount, 10, 1000, 0, guiWidgetFlags);
    {
      if (ImGui::IsItemDeactivatedAfterEdit()) {
        initializeParticle(particleCount, numOfParticleColor);
      }
    };
    ImGui::PopID();
    ImGui::SameLine();
    HelpMarker("This changes the number of particles for each colour");

    ImGui::Text("Types of Colour");
    (ImGui::SliderInt(" ", &numOfParticleColor, 2, 8, 0, guiWidgetFlags));
    {
      if (ImGui::IsItemDeactivatedAfterEdit()) {
        initializeParticle(particleCount, numOfParticleColor);
      }
    }
    ImGui::SameLine();
    HelpMarker(
        "This changes the number of different colours in the simulation");

    if (ImGui::Button("Refresh")) {
      initializeParticle(particleCount, numOfParticleColor);
    }
    ImGui::SeparatorText("Force Controls");
    if (ImGui::Button("Random Forces")) {
      populateRandomForce();
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset Force")) {
      resetForce();
    }
    ImGui::SameLine();
    if (ImGui::Button("Default Force")) {
      defaultForce();
    }
    if (ImGui::TreeNode("Red")) {
      ImGui::SliderFloat("R x R", &Force[RED][RED], -1, 1, 0, guiWidgetFlags);

      checkBool(RED, GREEN, "R x G");
      checkBool(RED, BLUE, "R x B");
      checkBool(RED, WHITE, "R x W");
      checkBool(RED, YELLOW, "R x Y");
      checkBool(RED, PURPLE, "R x P");
      checkBool(RED, CYAN, "R x C");
      checkBool(RED, MAGENTA, "R x M");

      ImGui::TreePop();
      ImGui::Spacing();
    }

    if (numOfParticleColor >= GREEN + 1) {
      if (ImGui::TreeNode("Green")) {
        ImGui::SliderFloat("G x R", &Force[GREEN][RED], -1, 1, 0,
                           guiWidgetFlags);

        checkBool(GREEN, GREEN, "G x G");
        checkBool(GREEN, BLUE, "G x B");
        checkBool(GREEN, WHITE, "G x W");
        checkBool(GREEN, YELLOW, "G x Y");
        checkBool(GREEN, PURPLE, "G x P");
        checkBool(GREEN, CYAN, "G x C");
        checkBool(GREEN, MAGENTA, "G x M");

        ImGui::TreePop();
        ImGui::Spacing();
      }
    }

    if (numOfParticleColor >= BLUE + 1) {
      if (ImGui::TreeNode("Blue")) {
        ImGui::SliderFloat("B x R", &Force[BLUE][RED], -1, 1, 0,
                           guiWidgetFlags);

        checkBool(BLUE, GREEN, "B x G");
        checkBool(BLUE, BLUE, "B x B");
        checkBool(BLUE, WHITE, "B x W");
        checkBool(BLUE, YELLOW, "B x Y");
        checkBool(BLUE, PURPLE, "B x P");
        checkBool(BLUE, CYAN, "B x C");
        checkBool(BLUE, MAGENTA, "B x M");

        ImGui::TreePop();
        ImGui::Spacing();
      }
    }

    if (numOfParticleColor >= WHITE + 1) {
      if (ImGui::TreeNode("White")) {
        ImGui::SliderFloat("W x R", &Force[WHITE][RED], -1, 1, 0,
                           guiWidgetFlags);

        checkBool(WHITE, GREEN, "W x G");
        checkBool(WHITE, BLUE, "W x B");
        checkBool(WHITE, WHITE, "W x W");
        checkBool(WHITE, YELLOW, "W x Y");
        checkBool(WHITE, PURPLE, "W x P");
        checkBool(WHITE, CYAN, "W x C");
        checkBool(WHITE, MAGENTA, "W x M");

        ImGui::TreePop();
        ImGui::Spacing();
      }
    }

    if (numOfParticleColor >= YELLOW + 1) {
      if (ImGui::TreeNode("Yellow")) {
        ImGui::SliderFloat("G x R", &Force[YELLOW][RED], -1, 1, 0,
                           guiWidgetFlags);

        checkBool(YELLOW, GREEN, "Y x G");
        checkBool(YELLOW, BLUE, "Y x B");
        checkBool(YELLOW, WHITE, "Y x W");
        checkBool(YELLOW, YELLOW, "Y x Y");
        checkBool(YELLOW, PURPLE, "Y x P");
        checkBool(YELLOW, CYAN, "Y x C");
        checkBool(YELLOW, MAGENTA, "Y x M");

        ImGui::TreePop();
        ImGui::Spacing();
      }
    }

    if (numOfParticleColor >= PURPLE + 1) {
      if (ImGui::TreeNode("Purple")) {
        ImGui::SliderFloat("P x R", &Force[PURPLE][RED], -1, 1, 0,
                           guiWidgetFlags);

        checkBool(PURPLE, GREEN, "P x G");
        checkBool(PURPLE, BLUE, "P x B");
        checkBool(PURPLE, WHITE, "P x W");
        checkBool(PURPLE, YELLOW, "P x Y");
        checkBool(PURPLE, PURPLE, "P x P");
        checkBool(PURPLE, CYAN, "P x C");
        checkBool(PURPLE, MAGENTA, "P x M");

        ImGui::TreePop();
        ImGui::Spacing();
      }
    }

    if (numOfParticleColor >= CYAN + 1) {
      if (ImGui::TreeNode("Cyan")) {
        ImGui::SliderFloat("C x R", &Force[CYAN][RED], -1, 1, 0,
                           guiWidgetFlags);

        checkBool(CYAN, GREEN, "C x G");
        checkBool(CYAN, BLUE, "C x B");
        checkBool(CYAN, WHITE, "C x W");
        checkBool(CYAN, YELLOW, "C x Y");
        checkBool(CYAN, PURPLE, "C x P");
        checkBool(CYAN, CYAN, "C x C");
        checkBool(CYAN, MAGENTA, "C x M");

        ImGui::TreePop();
        ImGui::Spacing();
      }
    }

    if (numOfParticleColor >= MAGENTA + 1) {
      if (ImGui::TreeNode("Magenta")) {
        ImGui::SliderFloat("M x R", &Force[MAGENTA][RED], -1, 1, 0,
                           guiWidgetFlags);

        checkBool(MAGENTA, GREEN, "M x G");
        checkBool(MAGENTA, BLUE, "M x B");
        checkBool(MAGENTA, WHITE, "M x W");
        checkBool(MAGENTA, YELLOW, "M x Y");
        checkBool(MAGENTA, PURPLE, "M x P");
        checkBool(MAGENTA, CYAN, "M x C");
        checkBool(MAGENTA, MAGENTA, "M x M");

        ImGui::TreePop();
        ImGui::Spacing();
      }
    }
    ImGui::End();
  }
  return QUIT;
}

void UI::close() {
  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
}

void UI::update(SDL_Renderer *renderer, double DeltaTime) {

  ImGuiIO &io = ImGui::GetIO();
  ImGui::Render();
  SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x,
                     io.DisplayFramebufferScale.y);
  SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
  SDL_RenderClear(renderer);
  ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

  updateParticle(DeltaTime / 1000);
  renderParticle(renderer);
}

void UI::setRadius(int Radius) { radius = Radius; }

UI::UI(int Width, int Height) : width(Width), height(Height) {
  srand(time(NULL));
  defaultForce();
}

void UI::populateRandomForce() {
  std::random_device rd;
  std::mt19937 gen(rd());

  // Define the distribution to generate numbers between -1 and 1
  std::uniform_real_distribution<> dis(-1.0, 1.0);

  // Fill the array with random values
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      Force[i][j] = dis(gen);
    }
  }
}

void UI::resetForce() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      Force[i][j] = 0;
    }
  }
}

void UI::defaultForce() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      Force[i][j] = defaultForceValue[i][j];
    }
  }
}

void UI::initializeParticle(int ParticleCount, int NumOfParticleColor) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> disX(0, width);
  std::uniform_real_distribution<> disY(0, height);
  particles.clear();
  for (int color = 0; color < NumOfParticleColor; color++) {
    for (int m = 0; m < ParticleCount; m++) {
      float x = disX(gen);
      float y = disY(gen);
      particles.emplace_back(x, y, color);
    }
  }
}

/* void UI::initializeParticle(int ParticleCount, int NumOfParticleColor) {
  particles.clear();
  int totalParticles = ParticleCount * NumOfParticleColor;
  int gridSize = std::ceil(std::sqrt(totalParticles));
  float cellWidth = static_cast<float>(width) / gridSize;
  float cellHeight = static_cast<float>(height) / gridSize;

  int index = 0;
  for (int color = 0; color < NumOfParticleColor; color++) {
    for (int m = 0; m < ParticleCount; m++) {
      int row = index / gridSize;
      int col = index % gridSize;

      // Add some randomness within each cell
      float offsetX = static_cast<float>(rand()) / RAND_MAX * cellWidth;
      float offsetY = static_cast<float>(rand()) / RAND_MAX * cellHeight;

      float x = col * cellWidth + offsetX;
      float y = row * cellHeight + offsetY;

      particles.emplace_back(x, y, color);
      index++;
    }
  }
} */

void UI::updateParticle(double DeltaTime) {
  for (auto &particle : particles) {
    particle.update(particles, width, height, DeltaTime, radius, Force);
  }
}

const std::vector<particle> &UI::getParticles() const { return particles; }

void UI::renderParticle(SDL_Renderer *Renderer) {
  const auto &particles = getParticles();
  for (const auto &particle : particles) {
    if (radius > 1) {
      particle.drawParticle(Renderer, radius);
    } else {
      particle.drawParticlePoint(Renderer);
    }
  }
}
