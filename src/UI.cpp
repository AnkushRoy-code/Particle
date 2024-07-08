#include "UI.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <SDL.h>
#include <ctime>
#include <iomanip>
#include <iostream>
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
    if (ImGui::Button("Quit Demo?")) {
      showDemoWindow = !showDemoWindow;
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

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // NOTE: force
    if (ImGui::TreeNode("Force Control")) {

      if (ImGui::Button("Random Forces")) {
        populateRandomForce();
      }
      ImGui::SameLine();
      if (ImGui::Button("Reset Force")) {
        resetForce();
      }
      ImGui::SameLine();
      if (ImGui::Button("Default Force")) {
        setDefaultForce();
      }

      ImGui::Spacing();
      ImGui::Separator();
      ImGui::Spacing();

      if (ImGui::Button("Save Forces To File")) {
        ImGui::LogToFile(2, "forces.txt");
        ImGui::SameLine();
        HelpMarker("These forces is saved inside forces.txt file");
      }
      showColorSliders();
      ImGui::LogFinish();

      ImGui::TreePop();
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // NOTE: min dist
    if (ImGui::TreeNode("Minimum Distance Control")) {

      if (ImGui::Button("Random Min Dist")) {
        populateRandomMinDistance();
      }
      ImGui::SameLine();
      if (ImGui::Button("Reset Min Dist")) {
        resetMinDistance();
      }
      if (ImGui::Button("Default MinDist")) {
        setDefaultMinDistance();
      }

      ImGui::Spacing();
      ImGui::Separator();
      ImGui::Spacing();

      if (ImGui::Button("Save Min Dist To File")) {
        ImGui::LogToFile(2, "minDist.txt");
        ImGui::SameLine();
        HelpMarker("These forces is saved inside minDist.txt file");
      }
      showMinDistSliders();
      ImGui::LogFinish();

      ImGui::TreePop();
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // NOTE: max dist
    if (ImGui::TreeNode("Maximum Distance Control")) {

      if (ImGui::Button("Random Max Dist")) {
        populateRandomMaxDistance();
      }
      ImGui::SameLine();
      if (ImGui::Button("Reset Max Dist")) {
        resetMaxDistance();
      }
      if (ImGui::Button("Default MaxDist")) {
        setDefaultMaxDistance();
      }

      ImGui::Spacing();
      ImGui::Separator();
      ImGui::Spacing();

      if (ImGui::Button("Save Min Dist To File")) {
        ImGui::LogToFile(2, "maxDist.txt");
        ImGui::SameLine();
        HelpMarker("These forces is saved inside maxDist.txt file");
      }
      showMaxDistSliders();
      ImGui::LogFinish();

      ImGui::TreePop();
    }
    ImGui::End();
  }
  if (showDemoWindow) {
    ImGui::ShowDemoWindow(&showDemoWindow);
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
  printForce();
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_real_distribution<> dis(-1.0, 1.0);

  // Fill the array with random values
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      Force[i][j] = dis(gen);
    }
  }
}

void UI::populateRandomMinDistance() {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_real_distribution<> dis(1, 20);

  // Fill the array with random values
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      minDist[i][j] = dis(gen);
    }
  }
}

void UI::populateRandomMaxDistance() {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_real_distribution<> dis(100, 300);

  // Fill the array with random values
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      maxDist[i][j] = dis(gen);
    }
  }
}

void UI::resetForce() {
  printForce();
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      Force[i][j] = 0;
    }
  }
}

void UI::resetMinDistance() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      minDist[i][j] = 0;
    }
  }
}

void UI::resetMaxDistance() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      minDist[i][j] = 0;
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

void UI::defaultMinDistance() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      minDist[i][j] = defaultMinDistanceValue[i][j];
    }
  }
}

void UI::defaultMaxDistance() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      maxDist[i][j] = defaultMaxDistanceValue[i][j];
    }
  }
}

void UI::setDefaultForce() {
  printForce();
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      Force[i][j] = defaultForceValue[i][j];
    }
  }
}

void UI::setDefaultMinDistance() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      minDist[i][j] = defaultMinDistanceValue[i][j];
    }
  }
}

void UI::setDefaultMaxDistance() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      maxDist[i][j] = defaultMaxDistanceValue[i][j];
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

void UI::updateParticle(double DeltaTime) {
  for (auto &particle : particles) {
    particle.update(particles, width, height, DeltaTime, radius, Force, minDist,
                    maxDist);
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
void UI::createColorTreeNode(const char *label, int colorIndex) {

  if (numOfParticleColor >= colorIndex + 1) {
    if (ImGui::TreeNode(label)) {
      for (int otherColor = 0; otherColor < COLOR_COUNT; ++otherColor) {
        std::string sliderLabel =
            std::string(label).substr(0, 1) + " x " + "RGBWYPCM"[otherColor];
        if (otherColor == colorIndex) {
          ImGui::SliderFloat(sliderLabel.c_str(),
                             &Force[colorIndex][otherColor], -1, 1, 0,
                             ImGuiSliderFlags_AlwaysClamp);
        } else {
          checkBool(colorIndex, static_cast<Color>(otherColor),
                    sliderLabel.c_str());
        }
      }
      ImGui::TreePop();
      ImGui::Spacing();
    }
  }
}

void UI::showColorSliders() {
  createColorTreeNode("Red", RED);
  createColorTreeNode("Green", GREEN);
  createColorTreeNode("Blue", BLUE);
  createColorTreeNode("White", WHITE);
  createColorTreeNode("Yellow", YELLOW);
  createColorTreeNode("Purple", PURPLE);
  createColorTreeNode("Cyan", CYAN);
  createColorTreeNode("Magenta", MAGENTA);
}

void UI::createMinDistTreeNode(const char *label, int colorIndex) {

  if (numOfParticleColor >= colorIndex + 1) {
    if (ImGui::TreeNode(label)) {
      for (int otherColor = 0; otherColor < COLOR_COUNT; ++otherColor) {
        std::string sliderLabel =
            std::string(label).substr(0, 1) + " x " + "RGBWYPCM"[otherColor];
        if (otherColor == colorIndex) {
          ImGui::SliderInt(sliderLabel.c_str(),
                           &minDist[colorIndex][otherColor], 1, 30, 0,
                           ImGuiSliderFlags_AlwaysClamp);
        } else {
          checkBool(colorIndex, static_cast<Color>(otherColor),
                    sliderLabel.c_str());
        }
      }
      ImGui::TreePop();
      ImGui::Spacing();
    }
  }
}

void UI::showMinDistSliders() {
  createMinDistTreeNode("Red", RED);
  createMinDistTreeNode("Green", GREEN);
  createMinDistTreeNode("Blue", BLUE);
  createMinDistTreeNode("White", WHITE);
  createMinDistTreeNode("Yellow", YELLOW);
  createMinDistTreeNode("Purple", PURPLE);
  createMinDistTreeNode("Cyan", CYAN);
  createMinDistTreeNode("Magenta", MAGENTA);
}

void UI::createMaxDistTreeNode(const char *label, int colorIndex) {

  if (numOfParticleColor >= colorIndex + 1) {
    if (ImGui::TreeNode(label)) {
      for (int otherColor = 0; otherColor < COLOR_COUNT; ++otherColor) {
        std::string sliderLabel =
            std::string(label).substr(0, 1) + " x " + "RGBWYPCM"[otherColor];
        if (otherColor == colorIndex) {
          ImGui::SliderInt(sliderLabel.c_str(),
                           &maxDist[colorIndex][otherColor], 150, 300, 0,
                           ImGuiSliderFlags_AlwaysClamp);
        } else {
          checkBool(colorIndex, static_cast<Color>(otherColor),
                    sliderLabel.c_str());
        }
      }
      ImGui::TreePop();
      ImGui::Spacing();
    }
  }
}

void UI::showMaxDistSliders() {
  createMaxDistTreeNode("RedMin", RED);
  createMaxDistTreeNode("GreenMin", GREEN);
  createMaxDistTreeNode("BlueMin", BLUE);
  createMaxDistTreeNode("WhiteMin", WHITE);
  createMaxDistTreeNode("YellowMin", YELLOW);
  createMaxDistTreeNode("PurpleMin", PURPLE);
  createMaxDistTreeNode("CyanMin", CYAN);
  createMaxDistTreeNode("MagentaMin", MAGENTA);
}

void UI::printForce() {
  const char *colorNames[COLOR_COUNT] = {"Red",    "Green",  "Blue", "White",
                                         "Yellow", "Purple", "Cyan", "Magenta"};

  std::cout << "\n\n\n<--START-->\n";
  std::cout << std::fixed
            << std::setprecision(2); // Set precision for floating-point values

  std::cout << std::setw(8) << " ";
  for (int i = 0; i < COLOR_COUNT; ++i) {
    std::cout << std::setw(8) << colorNames[i];
  }
  std::cout << std::endl;

  for (int i = 0; i < COLOR_COUNT; ++i) {
    std::cout << std::setw(8) << colorNames[i];
    for (int j = 0; j < COLOR_COUNT; ++j) {
      std::cout << std::setw(8) << Force[i][j];
    }
    std::cout << std::endl;
  }
  std::cout << "<--END-->\n";
}
