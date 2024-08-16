#pragma once

#include "color.h"
#include "particle.h"

#include <SDL.h>
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

  private:
    int width;
    int height;
    int radius              = 3;
    int particleCount       = 100;
    int numOfParticleColor  = 4;
    int ImGuiWindowWidth    = 360;
    int sameMinDist         = 5;
    int sameMaxDist         = 250;
    bool showDemoWindow     = false;
    bool showMinDistControl = false;
    bool showMaxDistControl = false;
    bool showSameMinDist    = false;
    bool showSameMaxDist    = false;
    bool wrap               = true;
    double deltaTime;
    float Force[COLOR_COUNT][COLOR_COUNT];
    int minDist[COLOR_COUNT][COLOR_COUNT];
    int maxDist[COLOR_COUNT][COLOR_COUNT];
    std::vector<particle> particles;

    // initial values
    static const float defaultForceValue[COLOR_COUNT][COLOR_COUNT];
    static const int defaultMinDistanceValue[COLOR_COUNT][COLOR_COUNT];
    static const int defaultMaxDistanceValue[COLOR_COUNT][COLOR_COUNT];
};
