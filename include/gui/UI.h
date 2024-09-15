#pragma once

#include "color.h"
#include "particle.h"
#include "font.h"
#include "imGuiInitialiser.h"
#include "imGuiElements.h"

#include <SDL.h>
#include <SDL_opengl.h>
#include <functional>
#include <string>
#include <vector>
#include <ctime>
#include <random>

#include <imgui.h>

class UI
{
  public:
    UI();
    void initializeParticle(int ParticleCount, int NumOfParticleColor);
    void initialise(SDL_Window *window, SDL_GLContext glContext, int Width, int Height);

    void setup();
    void close();

    void update(SDL_Window *Window,
                SDL_GLContext glContext,
                double DeltaTime,
                float Scale,
                float OffSetX,
                float OffSetY);

    void updateParticle(double DeltaTime);

    const std::vector<particle> &getParticles() const;

    void renderParticle(
        SDL_Window *Window, SDL_GLContext glContext, float Scale, float OffSetX, float OffSetY);

    void setRadius(int Radius);
    void setSize(int Width, int Height);

  private:
    SDL_Vertex calcParticlePos(
        int Radius, float Scale, float OffSetX, float OffSetY, float x, float y, int color) const;

  private:
    imGuiManager m_imguiManager;
    imGuiElementsManager m_imGuiElements;

    int m_width;
    int m_height;
    int m_radius              = 3;
    int m_particleCount       = 100;
    int m_numOfParticleColor  = 4;
    int m_ImGuiWindowWidth    = 360;
    int m_sameMinDist         = 5;
    int m_sameMaxDist         = 250;
    bool m_showDemoWindow     = false;
    bool m_showMinDistControl = false;
    bool m_showMaxDistControl = false;
    bool m_showSameMinDist    = false;
    bool m_showSameMaxDist    = false;
    bool m_wrap               = true;
    double m_deltaTime;
    float m_Force[COLOR_COUNT][COLOR_COUNT];
    int m_minDist[COLOR_COUNT][COLOR_COUNT];
    int m_maxDist[COLOR_COUNT][COLOR_COUNT];
    std::vector<particle> m_particles;

    std::vector<int> generateIndices(int numRects);
    static const SDL_Color ColorMap[COLOR_COUNT];
    // initial values
    static const float defaultForceValue[COLOR_COUNT][COLOR_COUNT];
    static const int defaultMinDistanceValue[COLOR_COUNT][COLOR_COUNT];
    static const int defaultMaxDistanceValue[COLOR_COUNT][COLOR_COUNT];
};
