#pragma once

#include "color.h"

#include <SDL.h>
#include <cstddef>
#include <vector>

class particles
{
  public:
    void update(const float &Width,
                const float &Height,
                const double &deltaTime,
                const std::array<std::array<float, COLOR_COUNT>, COLOR_COUNT> &Force,
                const std::array<std::array<int, COLOR_COUNT>, COLOR_COUNT> &MinDist,
                const std::array<std::array<int, COLOR_COUNT>, COLOR_COUNT> &MaxDist);

    void addParticle(float x, float y, int color);
    void clear();
    size_t size();
    [[nodiscard]] const std::vector<float> &getXPositions() const;
    [[nodiscard]] const std::vector<float> &getYPositions() const;
    [[nodiscard]] const std::vector<int> &getColors() const;

    void wrapAround(float Width, float Height);

  private:
    std::vector<float> m_xPositions {};
    std::vector<float> m_yPositions {};
    std::vector<float> m_xVelocity {};
    std::vector<float> m_yVelocity {};
    std::vector<int> m_colors {};

  private:
    /// Wraps particles around the viewport
};
