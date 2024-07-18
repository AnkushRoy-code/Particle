// this is the file I worked the most on.

#include "UI.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <SDL.h>
#include <ctime>
#include <random>

// guess what it initializes dear imgui.
void UI::initialize(SDL_Window *window, SDL_Renderer *renderer) {

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO &io = ImGui::GetIO();

  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiTreeNodeFlags_DefaultOpen;

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

// stole from the imgui.h/cpp file
static void HelpMarker(const char *desc) {
  ImGui::TextDisabled("(?)");
  if (ImGui::BeginItemTooltip()) {
    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
    ImGui::TextUnformatted(desc);
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();
  }
}

// idk... don't fall for the name. It makes a slider for the provided
// parameters.
void UI::checkBool(int start, int end, const char *string) {
  if (numOfParticleColor >= end + 1) {
    ImGui::SliderFloat(string, &Force[start][end], -1, 1, "%.3f",
                       ImGuiSliderFlags_AlwaysClamp);
  }
}

void UI::checkBoolMinDist(int start, int end, const char *string) {
  if (numOfParticleColor >= end + 1) {
    ImGui::SliderInt(string, &minDist[start][end], 1, 30, "%d",
                     ImGuiSliderFlags_AlwaysClamp);
  }
}

void UI::checkBoolMaxDist(int start, int end, const char *string) {
  if (numOfParticleColor >= end + 1) {
    ImGui::SliderInt(string, &maxDist[start][end], 150, 300, "%d",
                     ImGuiSliderFlags_AlwaysClamp);
  }
}

// didn't find a better name. What it does is setup and run the imgui stuff.
bool UI::setup() {

  ImGui_ImplSDLRenderer2_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();

  bool QUIT = false;
  auto guiWidgetFlags =
      ImGuiSliderFlags_AlwaysClamp; // i thought i'd use more flags.
  {

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(360, 720), ImGuiCond_Once);

    ImGui::Begin("Control Panel", NULL,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking);

    // idk why but wrapping it(window contents) with '{}' doesn't work.
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

    if (!showSameMinDist) {
      ImGui::Checkbox("Show MinDist Control", &showMinDistControl);
      if (!showMinDistControl) {
        ImGui::SameLine();
      }
    }
    if (!showMinDistControl) {
      ImGui::Checkbox("Same Min Width?##3", &showSameMinDist);
    }

    if (showSameMinDist) {
      if (ImGui::SliderInt("Minimum dist", &sameMinDist, 1, 30, 0,
                           guiWidgetFlags)) {
        changeAllMin(sameMinDist);
      }
    }

    if (!showSameMaxDist) {
      ImGui::Checkbox("Show MaxDist Control", &showMaxDistControl);
      if (!showMaxDistControl) {
        ImGui::SameLine();
      }
    }
    if (!showMaxDistControl) {
      ImGui::Checkbox("Same Max Width?##3", &showSameMaxDist);
    }

    if (showSameMaxDist) {
      if (ImGui::SliderInt("Maximum dist", &sameMaxDist, 150, 300, 0,
                           guiWidgetFlags)) {
        changeAllMax(sameMaxDist);
      }
    }

    // NOTE: force
    if (ImGui::CollapsingHeader("Focus Control")) {

      if (ImGui::Button("Random Forces")) {
        populateRandomForce();
      }
      ImGui::SameLine();
      if (ImGui::Button("Reset Force")) {
        resetForce();
      }
      ImGui::SameLine();
      if (ImGui::Button("Minimise Force")) {
        minimiseForce();
      }
      if (ImGui::Button("Maximise Force")) {
        maximiseForce();
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

        // FIX: This helper line doesn't show fsr and the ones later on like
        // this
        ImGui::SameLine();
        HelpMarker("These forces is saved inside forces.txt file");
      }
      showColorSliders();
      ImGui::LogFinish();
    }

    // NOTE: min dist
    if (showMinDistControl) {
      if (ImGui::CollapsingHeader("Minimum Distance Control")) {

        if (ImGui::Button("Random Min Dist")) {
          populateRandomMinDistance();
        }
        ImGui::SameLine();
        if (ImGui::Button("Minimise Min Dist")) {
          minimiseMinDistance();
        }
        if (ImGui::Button("Maximise Min Distance")) {
          maximiseMinDistance();
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
      }
    }

    // NOTE: max dist
    if (showMaxDistControl) {
      if (ImGui::CollapsingHeader("Maximum Distance Control")) {

        if (ImGui::Button("Random Max Dist")) {
          populateRandomMaxDistance();
        }
        ImGui::SameLine();
        if (ImGui::Button("Minimise Max Dist")) {
          minimiseMaxDistance();
        }
        if (ImGui::Button("Maximise Max Distance")) {
          maximiseMaxDistance();
        }
        if (ImGui::Button("Default MaxDist")) {
          setDefaultMaxDistance();
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::Button("Save Max Dist To File")) {
          ImGui::LogToFile(2, "maxDist.txt");
          ImGui::SameLine();
          HelpMarker("These forces is saved inside maxDist.txt file");
        }
        showMaxDistSliders();
        ImGui::LogFinish();
      }
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

// why is the constructor in the middle of the screen?
// because I am lazy.
UI::UI(int Width, int Height) : width(Width), height(Height) {
  srand(time(NULL));
  defaultForce();
  defaultMinDistance();
  defaultMaxDistance();
}

void UI::populateRandomForce() {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_real_distribution<> dis(-1.0, 1.0);

  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      Force[i][j] = dis(gen);
    }
  }
}

void UI::populateRandomMinDistance() {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_real_distribution<> dis(10, 30);

  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      minDist[i][j] = dis(gen);
    }
  }
}

void UI::populateRandomMaxDistance() {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_real_distribution<> dis(150, 300);

  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      maxDist[i][j] = dis(gen);
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

void UI::minimiseForce() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      Force[i][j] = -1.0f;
    }
  }
}

void UI::minimiseMinDistance() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      minDist[i][j] = 1;
    }
  }
}

void UI::minimiseMaxDistance() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      maxDist[i][j] = 150;
    }
  }
}

void UI::maximiseForce() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      Force[i][j] = 1.0f;
    }
  }
}

void UI::maximiseMinDistance() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      minDist[i][j] = 30;
    }
  }
}

void UI::maximiseMaxDistance() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      maxDist[i][j] = 300;
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
void UI::changeAllMin(int value) {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      minDist[i][j] = value;
    }
  }
}
void UI::changeAllMax(int value) {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      maxDist[i][j] = value;
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
    particle.update(particles, width, height, DeltaTime, Force, minDist,
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

// the section below is responsible for making the treenodes. took help from
// internet for most/all of this. and yeah I don't fully understand only this
// part of my code. please explain if you do.
void UI::createColorTreeNode(const char *label, int colorIndex) {
  if (numOfParticleColor >= colorIndex + 1) {
    if (ImGui::TreeNode(label)) {
      for (int otherColor = 0; otherColor < COLOR_COUNT; ++otherColor) {
        std::string sliderLabel =
            std::string(label).substr(0, 1) + " x " + "RGBWYPCM"[otherColor] +
            "##Force" + std::to_string(colorIndex) + std::to_string(otherColor);
        if (otherColor == colorIndex) {
          ImGui::SliderFloat(sliderLabel.c_str(),
                             &Force[colorIndex][otherColor], -1, 1, "%.2f",
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

void UI::createMinDistTreeNode(const char *label, int colorIndex) {
  if (numOfParticleColor >= colorIndex + 1) {
    if (ImGui::TreeNode(label)) {
      for (int otherColor = 0; otherColor < COLOR_COUNT; ++otherColor) {
        std::string sliderLabel = std::string(label).substr(0, 1) + " x " +
                                  "RGBWYPCM"[otherColor] + "##MinDist" +
                                  std::to_string(colorIndex) +
                                  std::to_string(otherColor);
        if (otherColor == colorIndex) {
          ImGui::SliderInt(sliderLabel.c_str(),
                           &minDist[colorIndex][otherColor], 1, 30, "%d",
                           ImGuiSliderFlags_AlwaysClamp);
        } else {
          checkBoolMinDist(colorIndex, static_cast<Color>(otherColor),
                           sliderLabel.c_str());
        }
      }
      ImGui::TreePop();
      ImGui::Spacing();
    }
  }
}

void UI::createMaxDistTreeNode(const char *label, int colorIndex) {
  if (numOfParticleColor >= colorIndex + 1) {
    if (ImGui::TreeNode(label)) {
      for (int otherColor = 0; otherColor < COLOR_COUNT; ++otherColor) {
        std::string sliderLabel = std::string(label).substr(0, 1) + " x " +
                                  "RGBWYPCM"[otherColor] + "##MaxDist" +
                                  std::to_string(colorIndex) +
                                  std::to_string(otherColor);
        if (otherColor == colorIndex) {
          ImGui::SliderInt(sliderLabel.c_str(),
                           &maxDist[colorIndex][otherColor], 150, 300, "%d",
                           ImGuiSliderFlags_AlwaysClamp);
        } else {
          checkBoolMaxDist(colorIndex, static_cast<Color>(otherColor),
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

void UI::showMinDistSliders() {
  createMinDistTreeNode("RedMin", RED);
  createMinDistTreeNode("GreenMin", GREEN);
  createMinDistTreeNode("BlueMin", BLUE);
  createMinDistTreeNode("WhiteMin", WHITE);
  createMinDistTreeNode("YellowMin", YELLOW);
  createMinDistTreeNode("PurpleMin", PURPLE);
  createMinDistTreeNode("CyanMin", CYAN);
  createMinDistTreeNode("MagentaMin", MAGENTA);
}

void UI::showMaxDistSliders() {
  createMaxDistTreeNode("RedMax", RED);
  createMaxDistTreeNode("GreenMax", GREEN);
  createMaxDistTreeNode("BlueMax", BLUE);
  createMaxDistTreeNode("WhiteMax", WHITE);
  createMaxDistTreeNode("YellowMax", YELLOW);
  createMaxDistTreeNode("PurpleMax", PURPLE);
  createMaxDistTreeNode("CyanMax", CYAN);
  createMaxDistTreeNode("MagentaMax", MAGENTA);
}
