#include "gui/imGuiElements.h"

//---------------------------------------------------------------------------
// Local Functions/Values
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Private Values
//---------------------------------------------------------------------------
const float imGuiElementsManager::defaultForceValue[COLOR_COUNT][COLOR_COUNT] = {
    // clang-format off
  
  //RED        GREEN    BLUE     WHITE    YELLOW   PURPLE  CYAN      MAGENTA
    {0.10f,    0.426f, -0.390f,  0.537f, -0.728f,  0.372f, 0.945f,  -0.535f},  // RED,
    {0.233f,  -0.87f,  -0.142f, -0.152f,  0.810f, -0.973f, 0.255f,  -0.645f},  // GREEN,
    {0.317f,  -0.724f, -0.09f,   0.987f, -0.233f,  0.593f, 0.601f,  -0.178f},  // BLUE,
    {0.709f,  -0.114f,  0.103f, -0.28f,   0.112f, -0.952f, -0.119f,  0.720f},  // WHITE,
    {0.452f,  -0.831f,  0.241f, -0.678f,  0.993f, -0.054f, 0.515f,  -0.407f},  // YELLOW,
    {-0.323f,  0.768f, -0.563f,  0.927f, -0.395f,  0.216f, -0.489f,  0.340f},  // PURPLE,
    {0.615f,  -0.129f,  0.853f, -0.577f,  0.434f, -0.762f, 0.261f,  -0.368f},  // CYAN,
    {0.287f,  -0.571f,  0.172f,  0.686f, -0.412f,  0.745f, -0.932f,  0.073f}   // MAGENTA
    // clang-format on
};
const int imGuiElementsManager::defaultMinDistanceValue[COLOR_COUNT][COLOR_COUNT] = {

    // clang-format off
  //RED GREEN BLUE WHITE YELLOW PURPLE CYAN MAGENTA
    {20, 20,  20,  20,   21,    27,    12,  8},   // RED,
    {20, 20,  20,  20,   26,    15,    24,  9},   // GREEN,
    {20, 20,  20,  20,    4,    29,    11,  23},  // BLUE,
    {20, 20,  20,  20,   14,    20,    30,  28},  // WHITE,
    {1 , 22,  25,   6,    3,    19,    10,  13},  // YELLOW,
    {30, 2,   5,   16,    8,    18,    14,  7},   // PURPLE,
    {11, 28,  23,   4,    9,    21,    17,  6},   // CYAN,
    {27, 12,  29,   1,   26,     3,    15,  24}   // MAGENTA
    // clang-format on
};
const int imGuiElementsManager::defaultMaxDistanceValue[COLOR_COUNT][COLOR_COUNT] = {
    // clang-format off
  //RED    GREEN BLUE  WHITE YELLOW PURPLE CYAN  MAGENTA
    {150,  150,  150,  150,  217,   259,   178,  294},  // RED,
    {150,  150,  150,  150,  239,   188,   195,  284},  // GREEN,
    {150,  150,  150,  150,  258,   293,   196,  263},  // BLUE,
    {150,  150,  150,  150,  201,   176,   269,  185},  // WHITE,
    {245,  289,  270,  186,  241,   200,   221,  198},  // YELLOW,
    {211,  179,  258,  272,  290,   184,   237,  205},  // PURPLE,
    {294,  196,  201,  248,  176,   284,   239,  170},  // CYAN,
    {169,  265,  288,  154,  275,   217,   230,  283}   // MAGENTA
    // clang-format on
};

void imGuiElementsManager::setup()
{
    {
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(360, m_height),
                                 ImGuiCond_Once);  // initial size
        ImGui::SetNextWindowSizeConstraints(ImVec2(320, m_height), ImVec2(500, m_height), 0, 0);

        ImGuiWindowFlags window_flags = 0;

        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoCollapse;
        /* window_flags |= ImGuiWindowFlags_MenuBar; */

        ImGuiWindowMain(window_flags);
    }

    if (m_showDemoWindow) { ImGui::ShowDemoWindow(&m_showDemoWindow); }
}

void imGuiElementsManager::ImGuiWindowMain(ImGuiWindowFlags WinFlags)
{
    if (ImGui::Begin(ICON_FA_SLIDERS " Control Panel", NULL, WinFlags))
    {
        ImGuiShowGlobalVariables();

        ImGuiShowForce();
        if (m_showMinDistControl) { ImGuiShowMinDist(); }
        if (m_showMaxDistControl) { ImGuiShowMaxDist(); }
        ImGui::End();
    }
}

void imGuiElementsManager::ImGuiShowGlobalVariables()
{
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate,
                io.Framerate);

    m_ImGuiWindowWidth = ImGui::GetWindowWidth();

    ImGui::SeparatorText(ICON_FA_GLOBE " Global variables");

    ImGui::SliderInt(ICON_FA_CIRCLE " Radius", &m_radius, 1, 10, 0, ImGuiSliderFlags_AlwaysClamp);

    ImGui::Text(ICON_FA_CUBES " Particle Count");
    ImGui::PushID(1);
    ImGui::SliderInt(" ", &m_particleCount, 10, 1000, 0, ImGuiSliderFlags_AlwaysClamp);
    {
        if (ImGui::IsItemDeactivatedAfterEdit())
        {
            /* initializeParticle(m_particleCount, m_numOfParticleColor); */
        }
    };
    ImGui::PopID();

    ImGui::Text(ICON_FA_PALETTE " Types of Colour");
    (ImGui::SliderInt(" ", &m_numOfParticleColor, 2, 8, 0, ImGuiSliderFlags_AlwaysClamp));
    {
        if (ImGui::IsItemDeactivatedAfterEdit())
        {
            /* initializeParticle(m_particleCount, m_numOfParticleColor); */
        }
    }

    if (ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT " Refresh"))
    {
        /* initializeParticle(m_particleCount, m_numOfParticleColor); */
    }
    ImGui::SameLine();
    ImGui::Checkbox(ICON_FA_EXPAND " Wrap Particles to viewport", &m_wrap);

    if (!m_showSameMinDist)
    {
        ImGui::Checkbox(ICON_FA_EYE " Show MinDist Control", &m_showMinDistControl);
        if (!m_showMinDistControl) { ImGui::SameLine(); }
    }
    if (!m_showMinDistControl) { ImGui::Checkbox(" Same Min Dist?##3", &m_showSameMinDist); }

    if (m_showSameMinDist)
    {
        if (ImGui::SliderInt(ICON_FA_RULER " Minimum dist", &m_sameMinDist, 1, 30, 0,
                             ImGuiSliderFlags_AlwaysClamp))
        {
            changeAllMin(m_sameMinDist);
        }
    }

    if (!m_showSameMaxDist)
    {
        ImGui::Checkbox(ICON_FA_EYE " Show MaxDist Control", &m_showMaxDistControl);
        if (!m_showMaxDistControl) { ImGui::SameLine(); }
    }
    if (!m_showMaxDistControl) { ImGui::Checkbox(" Same Max Dist?##3", &m_showSameMaxDist); }

    if (m_showSameMaxDist)
    {
        if (ImGui::SliderInt(ICON_FA_RULER " Maximum dist", &m_sameMaxDist, 150, 300, 0,
                             ImGuiSliderFlags_AlwaysClamp))
        {
            changeAllMax(m_sameMaxDist);
        }
    }
}

void imGuiElementsManager::ImGuiShowForce()
{
    if (ImGui::CollapsingHeader(ICON_FA_BOLT " Force Control"))
    {
        if (ImGui::Button(ICON_FA_DICE " Random Forces")) { populateRandomForce(); }

        ImGui::SameLine();

        if (ImGui::Button(ICON_FA_ARROW_ROTATE_LEFT " Reset Force")) { resetForce(); }

        ImGui::SameLine();

        if (ImGui::Button(ICON_FA_MINIMIZE " Minimise Force")) { minimiseForce(); }
        if (ImGui::Button(ICON_FA_MAXIMIZE " Maximise Force")) { maximiseForce(); }

        ImGui::SameLine();

        if (ImGui::Button(ICON_FA_GEAR " Default Force")) { setDefaultForce(); }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::Button(ICON_FA_FLOPPY_DISK " Save Forces To File"))
        {
            ImGui::LogToFile(2, "forces.txt");
        }
        showColorSliders();
        ImGui::LogFinish();
    }
}

void imGuiElementsManager::ImGuiShowMinDist()
{
    if (ImGui::CollapsingHeader("Minimum Distance Control"))
    {
        if (ImGui::Button(ICON_FA_DICE " Random Min Dist")) { populateRandomMinDistance(); }

        ImGui::SameLine();

        if (ImGui::Button(ICON_FA_MINIMIZE " Minimise Min Dist")) { minimiseMinDistance(); }
        if (ImGui::Button(ICON_FA_MAXIMIZE " Maximise Min Distance")) { maximiseMinDistance(); }
        if (ImGui::Button(ICON_FA_GEAR " Default MinDist")) { setDefaultMinDistance(); }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::Button(ICON_FA_FLOPPY_DISK " Save Min Dist To File"))
        {
            ImGui::LogToFile(2, "minDist.txt");
        }

        showMinDistSliders();
        ImGui::LogFinish();
    }
}

void imGuiElementsManager::ImGuiShowMaxDist()
{
    if (ImGui::CollapsingHeader("Maximum Distance Control"))
    {

        if (ImGui::Button(ICON_FA_DICE " Random Max Dist")) { populateRandomMaxDistance(); }

        ImGui::SameLine();

        if (ImGui::Button(ICON_FA_MINIMIZE " Minimise Max Dist")) { minimiseMaxDistance(); }
        if (ImGui::Button(ICON_FA_MAXIMIZE " Maximise Max Distance")) { maximiseMaxDistance(); }
        if (ImGui::Button(ICON_FA_GEAR " Default MaxDist")) { setDefaultMaxDistance(); }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::Button(ICON_FA_FLOPPY_DISK " Save Max Dist To File"))
        {
            ImGui::LogToFile(2, "maxDist.txt");
        }

        showMaxDistSliders();
        ImGui::LogFinish();
    }
}

void imGuiElementsManager::setRadius(int Radius) { m_radius = Radius; }

// idk... don't fall for the name. It makes a slider for the provided
// parameters.
void imGuiElementsManager::checkBool(int start, int end, const char *string)
{
    if (m_numOfParticleColor >= end + 1)
    {
        ImGui::SliderFloat(string, &m_Force[start][end], -1, 1, "%.3f",
                           ImGuiSliderFlags_AlwaysClamp);
    }
}

void imGuiElementsManager::checkBoolMinDist(int start, int end, const char *string)
{
    if (m_numOfParticleColor >= end + 1)
    {
        ImGui::SliderInt(string, &m_minDist[start][end], 1, 30, "%d", ImGuiSliderFlags_AlwaysClamp);
    }
}

void imGuiElementsManager::checkBoolMaxDist(int start, int end, const char *string)
{
    if (m_numOfParticleColor >= end + 1)
    {
        ImGui::SliderInt(string, &m_maxDist[start][end], 150, 300, "%d",
                         ImGuiSliderFlags_AlwaysClamp);
    }
}

void imGuiElementsManager::populateRandomForce()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(-1.0, 1.0);

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_Force[i][j] = dis(gen);
        }
    }
}

void imGuiElementsManager::populateRandomMinDistance()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(10, 30);

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_minDist[i][j] = dis(gen);
        }
    }
}

void imGuiElementsManager::populateRandomMaxDistance()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(150, 300);

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_maxDist[i][j] = dis(gen);
        }
    }
}

void imGuiElementsManager::resetForce()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_Force[i][j] = 0;
        }
    }
}

void imGuiElementsManager::minimiseForce()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_Force[i][j] = -1.0f;
        }
    }
}

void imGuiElementsManager::minimiseMinDistance()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_minDist[i][j] = 1;
        }
    }
}

void imGuiElementsManager::minimiseMaxDistance()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_maxDist[i][j] = 150;
        }
    }
}

void imGuiElementsManager::maximiseForce()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_Force[i][j] = 1.0f;
        }
    }
}

void imGuiElementsManager::maximiseMinDistance()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_minDist[i][j] = 30;
        }
    }
}

void imGuiElementsManager::maximiseMaxDistance()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_maxDist[i][j] = 300;
        }
    }
}

void imGuiElementsManager::defaultForce()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_Force[i][j] = defaultForceValue[i][j];
        }
    }
}

void imGuiElementsManager::defaultMinDistance()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_minDist[i][j] = defaultMinDistanceValue[i][j];
        }
    }
}

void imGuiElementsManager::defaultMaxDistance()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_maxDist[i][j] = defaultMaxDistanceValue[i][j];
        }
    }
}

void imGuiElementsManager::setDefaultForce()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_Force[i][j] = defaultForceValue[i][j];
        }
    }
}

void imGuiElementsManager::setDefaultMinDistance()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_minDist[i][j] = defaultMinDistanceValue[i][j];
        }
    }
}

void imGuiElementsManager::setDefaultMaxDistance()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_maxDist[i][j] = defaultMaxDistanceValue[i][j];
        }
    }
}

void imGuiElementsManager::setSize(int Width, int Height)
{
    m_width  = Width;
    m_height = Height;
}

void imGuiElementsManager::changeAllMin(int value)
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_minDist[i][j] = value;
        }
    }
}
void imGuiElementsManager::changeAllMax(int value)
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            m_maxDist[i][j] = value;
        }
    }
}

// the section below is responsible for making the treenodes. took help from
// internet for most/all of this. and yeah I don't fully understand only this
// part of my code. please explain if you do.
void imGuiElementsManager::createTreeNodeWithSliders(
    const char *label,
    int colorIndex,
    std::function<void(const std::string &, int, int)> sliderFunc)
{
    /*  this function alone is the creation of chatGPT IDK anything about
     * std::function. The code was too much nested so and was bothering me so I
     * asked gpt for this. */
    if (m_numOfParticleColor < colorIndex + 1) return;

    if (!ImGui::TreeNode(label)) return;

    for (int otherColor = 0; otherColor < COLOR_COUNT; ++otherColor)
    {
        std::string sliderLabel = std::string(label).substr(0, 1) + " x " + "RGBWYPCM"[otherColor]
                                  + "##" + std::to_string(colorIndex) + std::to_string(otherColor);

        sliderFunc(sliderLabel, colorIndex, otherColor);
    }

    ImGui::TreePop();
    ImGui::Spacing();
}

void imGuiElementsManager::createColorTreeNode(const char *label, int colorIndex)
{
    createTreeNodeWithSliders(
        label, colorIndex,
        [this](const std::string &sliderLabel, int colorIndex, int otherColor)
        {
            if (otherColor == colorIndex)
            {
                ImGui::SliderFloat(sliderLabel.c_str(), &m_Force[colorIndex][otherColor], -1, 1,
                                   "%.2f", ImGuiSliderFlags_AlwaysClamp);
            }
            else { checkBool(colorIndex, static_cast<Color>(otherColor), sliderLabel.c_str()); }
        });
}

void imGuiElementsManager::createMinDistTreeNode(const char *label, int colorIndex)
{
    createTreeNodeWithSliders(
        label, colorIndex,
        [this](const std::string &sliderLabel, int colorIndex, int otherColor)
        {
            if (otherColor == colorIndex)
            {
                ImGui::SliderInt(sliderLabel.c_str(), &m_minDist[colorIndex][otherColor], 1, 30,
                                 "%d", ImGuiSliderFlags_AlwaysClamp);
            }
            else
            {
                checkBoolMinDist(colorIndex, static_cast<Color>(otherColor), sliderLabel.c_str());
            }
        });
}

void imGuiElementsManager::createMaxDistTreeNode(const char *label, int colorIndex)
{
    createTreeNodeWithSliders(
        label, colorIndex,
        [this](const std::string &sliderLabel, int colorIndex, int otherColor)
        {
            if (otherColor == colorIndex)
            {
                ImGui::SliderInt(sliderLabel.c_str(), &m_maxDist[colorIndex][otherColor], 150, 300,
                                 "%d", ImGuiSliderFlags_AlwaysClamp);
            }
            else
            {
                checkBoolMaxDist(colorIndex, static_cast<Color>(otherColor), sliderLabel.c_str());
            }
        });
}

void imGuiElementsManager::showColorSliders()
{
    createColorTreeNode("Red", RED);
    createColorTreeNode("Green", GREEN);
    createColorTreeNode("Blue", BLUE);
    createColorTreeNode("White", WHITE);
    createColorTreeNode("Yellow", YELLOW);
    createColorTreeNode("Purple", PURPLE);
    createColorTreeNode("Cyan", CYAN);
    createColorTreeNode("Magenta", MAGENTA);
}

void imGuiElementsManager::showMinDistSliders()
{
    createMinDistTreeNode("RedMin", RED);
    createMinDistTreeNode("GreenMin", GREEN);
    createMinDistTreeNode("BlueMin", BLUE);
    createMinDistTreeNode("WhiteMin", WHITE);
    createMinDistTreeNode("YellowMin", YELLOW);
    createMinDistTreeNode("PurpleMin", PURPLE);
    createMinDistTreeNode("CyanMin", CYAN);
    createMinDistTreeNode("MagentaMin", MAGENTA);
}

void imGuiElementsManager::showMaxDistSliders()
{
    createMaxDistTreeNode("RedMax", RED);
    createMaxDistTreeNode("GreenMax", GREEN);
    createMaxDistTreeNode("BlueMax", BLUE);
    createMaxDistTreeNode("WhiteMax", WHITE);
    createMaxDistTreeNode("YellowMax", YELLOW);
    createMaxDistTreeNode("PurpleMax", PURPLE);
    createMaxDistTreeNode("CyanMax", CYAN);
    createMaxDistTreeNode("MagentaMax", MAGENTA);
}
