#include "gui/imGuiInitialiser.h"

void imGuiManager::initialise(SDL_Window *window, SDL_GLContext glContext)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();

    // Fonts
    io.Fonts->AddFontDefault();
    ImFontConfig iconsConfig;
    iconsConfig.MergeMode              = true;
    iconsConfig.PixelSnapH             = true;
    iconsConfig.GlyphMinAdvanceX       = 12.0f;
    static const ImWchar icon_ranges[] = {ICON_MIN_FA, ICON_MAX_FA, 0};

    io.Fonts->AddFontFromFileTTF(FONT_ICON_FILE_NAME_FAS, 12.0f, &iconsConfig, icon_ranges);

    // Inputs
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiTreeNodeFlags_DefaultOpen;

    // Theme
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 330");

    // For some friendly looking buttons
    ImGuiStyle &style        = ImGui::GetStyle();
    style.FrameRounding      = 5.0f;
    style.GrabRounding       = 12.0f;
    style.WindowTitleAlign   = ImVec2(0.5f, 0.5f);
    style.SeparatorTextAlign = ImVec2(0.5f, 0.5f);
}

void imGuiManager::setup()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void imGuiManager::close()
{
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}
