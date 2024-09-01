#pragma once

#include "color.h"
#include "particle.h"

#include <SDL.h>
#include <SDL_render.h>
#include <functional>
#include <imgui.h>
#include <string>
#include <vector>

class UI
{
  public:
    UI();
    void initializeParticle(int ParticleCount, int NumOfParticleColor);
    void initialize(SDL_Window *window,
                    SDL_Renderer *renderer,
                    int Width,
                    int Height);

    void setup();
    void close();

    void update(SDL_Renderer *renderer,
                double DeltaTime,
                float Scale,
                float OffSetX,
                float OffSetY);

    void updateParticle(double DeltaTime);

    const std::vector<particle> &getParticles() const;

    void renderParticle(SDL_Renderer *Renderer,
                        float Scale,
                        float OffSetX,
                        float OffSetY);

    void setRadius(int Radius);
    void setSize(int Width, int Height);

  private:
    void createColorTreeNode(const char *label, int colorIndex);
    void createMinDistTreeNode(const char *label, int colorIndex);
    void createMaxDistTreeNode(const char *label, int colorIndex);
    void createTreeNodeWithSliders(
        const char *label,
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
    void ImGuiShowMenuBar();
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
    SDL_Vertex calcParticlePos(int Radius,
                               float Scale,
                               float OffSetX,
                               float OffSetY,
                               float x,
                               float y,
                               int color) const;

  private:
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
