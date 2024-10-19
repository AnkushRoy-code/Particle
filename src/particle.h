#pragma once

#include "color.h"

#include <SDL.h>
#include <vector>

class particle
{
  public:
    particle(float X, float Y, int Color);

    void update(const std::vector<particle> &Particles,
                float Width,
                float Height,
                double deltaTime,
                float Force[COLOR_COUNT][COLOR_COUNT],
                int MinDist[COLOR_COUNT][COLOR_COUNT],
                int MaxDist[COLOR_COUNT][COLOR_COUNT],
                int ImGuiWindowWidth);

    float getPosX() const;
    float getPosY() const;
    int getColor() const { return m_color; }
    void setPos(int X, int Y)
    {
        m_x = X;
        m_y = Y;
    }

  private:
    float m_x;
    float m_y;
    float m_vx;
    float m_vy;
    int m_color;
    int m_ImGuiWindowWidth = 360;

    // Force/minDist/maxDist setup
    // Colors -> Red(0), Green(1), Blue(2), White(3),
    // Yellow(4), Purple(5), Cyan(6), Magenta(7)

    float m_force[COLOR_COUNT][COLOR_COUNT];
    int m_minDist[COLOR_COUNT][COLOR_COUNT];
    int m_maxDist[COLOR_COUNT][COLOR_COUNT];

  private:
    void wrapAround(float Width, float Height);

    void handleMouseWheel(const SDL_Event &event);
    void handleMouseButtonDown(const SDL_Event &event);
    void handleMouseButtonUp(const SDL_Event &event);
    void handleKeyDown(const SDL_Event &event);
};
