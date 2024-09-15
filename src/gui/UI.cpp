// this is the file I worked the most on.

#include "gui/UI.h"
#include "gui/imGuiInitialiser.h"

//---------------------------------------------------------------------------
// Local Functions/Values
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Private Values
//---------------------------------------------------------------------------
const SDL_Color UI::ColorMap[COLOR_COUNT] {
    {255, 0, 0, 255},      // RED
    {0, 255, 0, 255},      // GREEN
    {0, 0, 255, 255},      // BLUE
    {255, 255, 255, 255},  // WHITE
    {255, 255, 25, 255},   // YELLOW
    {145, 30, 180, 255},   // PURPLE
    {70, 240, 240, 255},   // CYAN
    {240, 50, 230, 255}    // MAGENTA
};

//---------------------------------------------------------------------------
// Implementation Of Functions
//---------------------------------------------------------------------------

UI::UI() { srand(time(NULL)); }

void UI::initializeParticle(int ParticleCount, int NumOfParticleColor)
{
    /* std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> disX(0, m_width);
    std::uniform_real_distribution<> disY(0, m_height);
    m_particles.clear();
    for (int color = 0; color < NumOfParticleColor; color++)
    {
        for (int m = 0; m < ParticleCount; m++)
        {
            float x = disX(gen);
            float y = disY(gen);
            m_particles.emplace_back(x, y, color);
        }
    } */
}

// guess what it initializes dear imgui.
void UI::initialise(SDL_Window *window, SDL_GLContext glContext, int Width, int Height)
{
    m_width  = Width - m_ImGuiWindowWidth;
    m_height = Height;

    m_imguiManager.initialise(window, glContext);

    /* initializeParticle(100, 4); */
}

void UI::setup()
{
    m_imguiManager.setup();
    m_imGuiElements.setup();
}

void UI::close() { m_imguiManager.close(); }

// didn't find a better name. What it does is setup and run the imgui stuff.
void UI::update(SDL_Window *Window,
                SDL_GLContext glContext,
                double DeltaTime,
                float Scale,
                float OffSetX,
                float OffSetY)
{

    ImGui::Render();
    glClearColor(0.09f, 0.09f, 0.09f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(Window);
    /* updateParticle(DeltaTime / 1000); */
    /* renderParticle(Window, glContext, Scale, OffSetX, OffSetY); */
}

void UI::updateParticle(double DeltaTime)
{
    /* for (auto &particle: m_particles)
    {
        particle.update(m_particles, m_width - m_ImGuiWindowWidth, m_height, DeltaTime, m_Force,
                        m_minDist, m_maxDist, m_ImGuiWindowWidth, m_wrap);
    } */
}

const std::vector<particle> &UI::getParticles() const
{
    // return m_particles;
}

std::vector<int> UI::generateIndices(int numRects)
{
    /* std::vector<int> indices;
    indices.reserve(numRects * 6);  // Pre-allocate space for efficiency

    for (int i = 0; i < numRects; ++i)
    {
        int baseIndex = i * 4;  // 4 vertices per rectangle

        // Triangle 1: (baseIndex, baseIndex+1, baseIndex+2)
        indices.push_back(baseIndex);
        indices.push_back(baseIndex + 1);
        indices.push_back(baseIndex + 2);

        // Triangle 2: (baseIndex, baseIndex+2, baseIndex+3)
        indices.push_back(baseIndex);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 3);
    }

    return indices; */
}

SDL_Vertex UI::calcParticlePos(
    int Radius, float Scale, float OffSetX, float OffSetY, float x, float y, int color) const
{
    /* // position
    SDL_Vertex rect;
    SDL_FPoint position;

    float scaledRadius = static_cast<float>(Radius + 1) * Scale / 2.0f;  // Center around particle

    position.x = (x * Scale) + OffSetX - scaledRadius + m_ImGuiWindowWidth;
    position.y = (y * Scale) + OffSetY - scaledRadius;
    rect       = {position, ColorMap[color], SDL_FPoint {1, 1}};

    return rect; */
}

void UI::renderParticle(
    SDL_Window *Window, SDL_GLContext glContext, float Scale, float OffSetX, float OffSetY)
{
}

void UI::setRadius(int Radius) { m_imGuiElements.setRadius(Radius); }
void UI::setSize(int Width, int Height) { m_imGuiElements.setSize(Width, Height); }
