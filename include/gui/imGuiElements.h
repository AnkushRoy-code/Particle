#pragma once

#include "color.h"
#include "font.h"

#include <SDL.h>
#include <SDL_opengl.h>
#include <functional>
#include <string>
#include <vector>
#include <ctime>
#include <random>
#include <imgui.h>

class imGuiElementsManager
{
  public:
    void setup();
    void close();

    void update(SDL_Window *Window,
                SDL_GLContext glContext,
                double DeltaTime,
                float Scale,
                float OffSetX,
                float OffSetY);

    void updateParticle(double DeltaTime);

    void renderParticle(
        SDL_Window *Window, SDL_GLContext glContext, float Scale, float OffSetX, float OffSetY);

    void setRadius(int Radius);
    void setSize(int Width, int Height);

  private:
    void createColorTreeNode(const char *label, int colorIndex);
    void createMinDistTreeNode(const char *label, int colorIndex);
    void createMaxDistTreeNode(const char *label, int colorIndex);
    void createTreeNodeWithSliders(const char *label,
                                   int colorIndex,
                                   std::function<void(const std::string &, int, int)> sliderFunc);
    void showColorSliders();
    void ImGuiWindowMain(ImGuiWindowFlags winFlags);
    void ImGuiShowGlobalVariables();
    void ImGuiShowForce();
    void ImGuiShowMaxDist();
    void ImGuiShowMinDist();
    void showMinDistSliders();
    void showMaxDistSliders();
    void populateRandomForce();
    void populateRandomMinDistance();
    void populateRandomMaxDistance();
    void resetForce();
    void minimiseForce();
    void minimiseMinDistance();
    void minimiseMaxDistance();
    void maximiseForce();
    void maximiseMinDistance();
    void maximiseMaxDistance();
    void defaultForce();
    void defaultMinDistance();
    void defaultMaxDistance();
    void setDefaultForce();
    void setDefaultMinDistance();
    void setDefaultMaxDistance();
    void changeAllMin(int value);
    void changeAllMax(int value);
    void checkBool(int start, int end, const char *string);
    void checkBoolMinDist(int start, int end, const char *string);
    void checkBoolMaxDist(int start, int end, const char *string);
    SDL_Vertex calcParticlePos(
        int Radius, float Scale, float OffSetX, float OffSetY, float x, float y, int color) const;

  private:
    int m_width;
    int m_height              = 500;
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

    // initial values
    static const float defaultForceValue[COLOR_COUNT][COLOR_COUNT];
    static const int defaultMinDistanceValue[COLOR_COUNT][COLOR_COUNT];
    static const int defaultMaxDistanceValue[COLOR_COUNT][COLOR_COUNT];
};
