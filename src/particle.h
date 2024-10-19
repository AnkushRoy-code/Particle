#pragma once

#include "color.h"

#include <SDL.h>
#include <cstddef>
#include <vector>

class particles
{
  public:
    particles()
    {
        m_xPositions.reserve(8000);  // 8k it the maximum amount of particles possible
        m_yPositions.reserve(8000);
        m_xVelocity.reserve(8000);
        m_yVelocity.reserve(8000);
        m_colors.reserve(8000);
    }

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
