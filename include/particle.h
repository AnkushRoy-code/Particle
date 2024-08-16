#pragma once

#include "color.h"

#include <SDL.h>
#include <vector>

class particle
{
  public:
    particle(float X, float Y, int Color);

    void drawParticle(SDL_Renderer *Renderer,
                      int Radius,
                      float Scale,
                      float OffSetX,
                      float OffSetY) const;

    void update(const std::vector<particle> &Particles,
                float Width,
                float Height,
                double deltaTime,
                float Force[COLOR_COUNT][COLOR_COUNT],
                int MinDist[COLOR_COUNT][COLOR_COUNT],
                int MaxDist[COLOR_COUNT][COLOR_COUNT],
                int ImGuiWindowWidth,
                bool Wrap);

    float getPosX() const;
    float getPosY() const;
    void setPos(int X, int Y)
    {
        x = X;
        y = Y;
    }

  private:
    float x, y, vx, vy;
    int color;
    int pImGuiWindowWidth = 360;
    void handleMouseWheel(const SDL_Event &event);
    void handleMouseButtonDown(const SDL_Event &event);
    void handleMouseButtonUp(const SDL_Event &event);
    void handleKeyDown(const SDL_Event &event);

    // Force/minDist/maxDist setup
    // Colors -> Red(0), Green(1), Blue(2), White(3),
    // Yellow(4), Purple(5), Cyan(6), Magenta(7)

    float force[COLOR_COUNT][COLOR_COUNT];
    int minDist[COLOR_COUNT][COLOR_COUNT];
    int maxDist[COLOR_COUNT][COLOR_COUNT];

  private:
    SDL_Rect calcParticleSize(int Radius,
                              float Scale,
                              float OffSetX,
                              float OffSetY) const;
    void wrapAround(float Width, float Height);
    void dontWrapAround(float Width, float Height);
};
