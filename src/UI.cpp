// this is the file I worked the most on.

#include "UI.h"
#include "color.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <SDL.h>
#include <ctime>
#include <random>

//---------------------------------------------------------------------------
// Local Functions/Values
//---------------------------------------------------------------------------

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

//---------------------------------------------------------------------------
// Private Values
//---------------------------------------------------------------------------
const float UI::defaultForceValue[COLOR_COUNT][COLOR_COUNT] = {
    // RED GREEN BLUE WHITE YELLOW PURPLE CYAN MAGENTA

    {0.10f, 0.426f, -0.390f, 0.537f, -0.728f, 0.372f, 0.945f, -0.535f}, // RED,
    {0.233f, -0.87f, -0.142f, -0.152f, 0.810f, -0.973f, 0.255f,
     -0.645f}, // GREEN,
    {0.317f, -0.724f, -0.09f, 0.987f, -0.233f, 0.593f, 0.601f,
     -0.178f}, // BLUE,
    {0.709f, -0.114f, 0.103f, -0.28f, 0.112f, -0.952f, -0.119f,
     0.720f}, // WHITE,
    {0.452f, -0.831f, 0.241f, -0.678f, 0.993f, -0.054f, 0.515f,
     -0.407f}, // YELLOW,
    {-0.323f, 0.768f, -0.563f, 0.927f, -0.395f, 0.216f, -0.489f,
     0.340f}, // PURPLE,
    {0.615f, -0.129f, 0.853f, -0.577f, 0.434f, -0.762f, 0.261f,
     -0.368f}, // CYAN,
    {0.287f, -0.571f, 0.172f, 0.686f, -0.412f, 0.745f, -0.932f,
     0.073f} // MAGENTA
};
const int UI::defaultMinDistanceValue[COLOR_COUNT][COLOR_COUNT] = {
    // RED GREEN BLUE WHITE YELLOW PURPLE CYAN MAGENTA

    {20, 20, 20, 20, 21, 27, 12, 8},  // RED,
    {20, 20, 20, 20, 26, 15, 24, 9},  // GREEN,
    {20, 20, 20, 20, 4, 29, 11, 23},  // BLUE,
    {20, 20, 20, 20, 14, 20, 30, 28}, // WHITE,
    {1, 22, 25, 6, 3, 19, 10, 13},    // YELLOW,
    {30, 2, 5, 16, 8, 18, 14, 7},     // PURPLE,
    {11, 28, 23, 4, 9, 21, 17, 6},    // CYAN,
    {27, 12, 29, 1, 26, 3, 15, 24}    // MAGENTA
};
const int UI::defaultMaxDistanceValue[COLOR_COUNT][COLOR_COUNT] = {
    // RED GREEN BLUE WHITE YELLOW PURPLE CYAN MAGENTA

    {150, 150, 150, 150, 217, 259, 178, 294}, // RED,
    {150, 150, 150, 150, 239, 188, 195, 284}, // GREEN,
    {150, 150, 150, 150, 258, 293, 196, 263}, // BLUE,
    {150, 150, 150, 150, 201, 176, 269, 185}, // WHITE,
    {245, 289, 270, 186, 241, 200, 221, 198}, // YELLOW,
    {211, 179, 258, 272, 290, 184, 237, 205}, // PURPLE,
    {294, 196, 201, 248, 176, 284, 239, 170}, // CYAN,
    {169, 265, 288, 154, 275, 217, 230, 283}  // MAGENTA
};

//---------------------------------------------------------------------------
// Implementation Of Functions
//---------------------------------------------------------------------------

UI::UI() {
  srand(time(NULL));
  defaultForce();
  defaultMinDistance();
  defaultMaxDistance();
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

// guess what it initializes dear imgui.
void UI::initialize(SDL_Window *window, SDL_Renderer *renderer, int Width,
                    int Height) {

  width = Width - ImGuiWindowWidth;
  height = Height;

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

void UI::setup() {

  ImGui_ImplSDLRenderer2_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();

  {

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(360, height),
                             ImGuiCond_Once); // initial size
    ImGui::SetNextWindowSizeConstraints(ImVec2(320, height),
                                        ImVec2(500, height), 0, 0);

    ImGuiWindowFlags window_flags = 0;

    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    /* window_flags |= ImGuiWindowFlags_MenuBar; */
    if (ImGui::Begin("Control Panel", NULL, window_flags)) {

      showGlobalVariables();

      showForce();
      if (showMinDistControl) {
        showMinDist();
      }
      if (showMaxDistControl) {
        showMaxDist();
      }
      ImGui::End();
    }
  }

  if (showDemoWindow) {
    ImGui::ShowDemoWindow(&showDemoWindow);
  }
}

// stolen from imgui_demo.cpp line 261.
// Helper to wire demo markers located in code to an interactive browser
typedef void (*ImGuiDemoMarkerCallback)(const char *file, int line,
                                        const char *section, void *user_data);
ImGuiDemoMarkerCallback GIiGuiDemoMarkerCallback = NULL;
void *GIiGuiDemoMarkerCallbackUserData = NULL;
#define IMGUI_DEMO_MARKER(section)                                             \
  do {                                                                         \
    if (GIiGuiDemoMarkerCallback != NULL)                                      \
      GIiGuiDemoMarkerCallback(__FILE__, __LINE__, section,                    \
                               GIiGuiDemoMarkerCallbackUserData);              \
  } while (0)

void UI::showMenuBar() {
  IMGUI_DEMO_MARKER("MENU");
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("Menu")) {
      if (ImGui::BeginMenu("Menu")) {
        ImGui::EndMenu();
      }
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }
}

void UI::showGlobalVariables() {
  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
              1000.0f / io.Framerate, io.Framerate);

  ImGuiWindowWidth = ImGui::GetWindowWidth();

  ImGui::SeparatorText("Global variables");

  ImGui::SliderInt("Radius", &radius, 1, 10, 0, ImGuiSliderFlags_AlwaysClamp);

  ImGui::Text("Particle Count");
  ImGui::PushID(1);
  ImGui::SliderInt(" ", &particleCount, 10, 1000, 0,
                   ImGuiSliderFlags_AlwaysClamp);
  {
    if (ImGui::IsItemDeactivatedAfterEdit()) {
      initializeParticle(particleCount, numOfParticleColor);
    }
  };
  ImGui::PopID();
  ImGui::SameLine();
  HelpMarker("This changes the number of particles for each colour");

  ImGui::Text("Types of Colour");
  (ImGui::SliderInt(" ", &numOfParticleColor, 2, 8, 0,
                    ImGuiSliderFlags_AlwaysClamp));
  {
    if (ImGui::IsItemDeactivatedAfterEdit()) {
      initializeParticle(particleCount, numOfParticleColor);
    }
  }
  ImGui::SameLine();
  HelpMarker("This changes the number of different colours in the simulation");

  if (ImGui::Button("Refresh")) {
    initializeParticle(particleCount, numOfParticleColor);
  }
  ImGui::SameLine();
  ImGui::Checkbox("Wrap Particles to viewport", &wrap);

  if (!showSameMinDist) {
    ImGui::Checkbox("Show MinDist Control", &showMinDistControl);
    if (!showMinDistControl) {
      ImGui::SameLine();
    }
  }
  if (!showMinDistControl) {
    ImGui::Checkbox("Same Min Dist?##3", &showSameMinDist);
  }

  if (showSameMinDist) {
    if (ImGui::SliderInt("Minimum dist", &sameMinDist, 1, 30, 0,
                         ImGuiSliderFlags_AlwaysClamp)) {
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
    ImGui::Checkbox("Same Max Dist?##3", &showSameMaxDist);
  }

  if (showSameMaxDist) {
    if (ImGui::SliderInt("Maximum dist", &sameMaxDist, 150, 300, 0,
                         ImGuiSliderFlags_AlwaysClamp)) {
      changeAllMax(sameMaxDist);
    }
  }
}

void UI::showForce() {
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
}

void UI::showMinDist() {
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

void UI::showMaxDist() {
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

void UI::close() {
  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
}

// didn't find a better name. What it does is setup and run the imgui stuff.
void UI::update(SDL_Renderer *renderer, double DeltaTime, float Scale,
                float OffSetX, float OffSetY) {

  ImGuiIO &io = ImGui::GetIO();
  ImGui::Render();
  SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x,
                     io.DisplayFramebufferScale.y);
  SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
  SDL_RenderClear(renderer);
  updateParticle(DeltaTime / 1000);
  renderParticle(renderer, Scale, OffSetX, OffSetY);
  ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
}

void UI::updateParticle(double DeltaTime) {
  for (auto &particle : particles) {
    particle.update(particles, width - ImGuiWindowWidth, height, DeltaTime,
                    Force, minDist, maxDist, ImGuiWindowWidth, wrap);
  }
}

const std::vector<particle> &UI::getParticles() const { return particles; }

void UI::renderParticle(SDL_Renderer *Renderer, float Scale, float OffSetX,
                        float OffSetY) {
  const auto &particles = getParticles();
  for (const auto &particle : particles) {
    particle.drawParticle(Renderer, radius, Scale, OffSetX, OffSetY);
  }
}

void UI::setRadius(int Radius) { radius = Radius; }

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

void UI::setSize(int Width, int Height) {
  width = Width;
  height = Height;
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
