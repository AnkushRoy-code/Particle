#include "particle.h"

#include "color.h"

#include <SDL.h>
#include <SDL_timer.h>
#include <cmath>
#include <cstddef>
#include <array>
//---------------------------------------------------------------------------
// Local Values
//---------------------------------------------------------------------------

// this is the width of the control pannel every particle is displaced this
// amount of distance to the right of the screen so they don't overlap.

//---------------------------------------------------------------------------
// Implementation Of Functions
//---------------------------------------------------------------------------

// this is the main logic of the particle simulation. This.... this function has
// the most maths/Physics that I implemented in this project, I knew the logic
// that I had to put here by other people that had made it or showcased it. But
// imblementating what I know in cpp was not as easy as it seemed, this function
// went through a lot of changes throughout the days.
void particles::update(const float &Width,
                       const float &Height,
                       const double &deltaTime,
                       const std::array<std::array<float, COLOR_COUNT>, COLOR_COUNT> &Force,
                       const std::array<std::array<int, COLOR_COUNT>, COLOR_COUNT> &MinDist,
                       const std::array<std::array<int, COLOR_COUNT>, COLOR_COUNT> &MaxDist)
{

    float halfWidth  = 0.5f * Width;
    float halfHeight = 0.5f * Height;

    const float dampingFactor = 0.95f;

    for (size_t i = 0; i < m_yPositions.size(); i++)
    {
        float xVelocity = m_xVelocity[i];
        float yVelocity = m_yVelocity[i];

        for (size_t j = 0; j < m_yPositions.size(); j++)
        {
            if (i == j) continue;  // Skip self-interaction

            float dx = m_xPositions[j] - m_xPositions[i];
            float dy = m_yPositions[j] - m_yPositions[i];

            // Wrap around particle force calculation
            if (dx > halfWidth) { dx -= Width; }
            else if (dx < -halfWidth) { dx += Width; }

            if (dy > halfHeight) { dy -= Height; }
            else if (dy < -halfHeight) { dy += Height; }

            // Calculate distance
            float distanceSquared = dx * dx + dy * dy;

            if (distanceSquared == 0.0f) continue;  // Skip if particles overlap

            int colorI = m_colors[i];
            int colorJ = m_colors[j];

            // Determine force based on distance
            float force          = 0.0f;
            float minDistSquared = MinDist[colorI][colorJ] * MinDist[colorI][colorJ];
            float maxDistSquared = MaxDist[colorI][colorJ] * MaxDist[colorI][colorJ];

            if (distanceSquared < minDistSquared)
            {
                force          = -1.0f;
                float distance = std::sqrt(distanceSquared);

                float fx = force * (dx / distance);
                float fy = force * (dy / distance);

                xVelocity += fx;
                yVelocity += fy;
            }

            else if (distanceSquared <= maxDistSquared)
            {
                force          = Force[colorI][colorJ];
                float distance = std::sqrt(distanceSquared);

                float fx = force * (dx / distance);
                float fy = force * (dy / distance);

                xVelocity += fx;
                yVelocity += fy;
            }
        }

        m_xPositions[i] += xVelocity * deltaTime;
        m_yPositions[i] += yVelocity * deltaTime;

        m_xVelocity[i] = xVelocity * dampingFactor;
        m_yVelocity[i] = yVelocity * dampingFactor;
    }

    wrapAround(Width, Height);
}

void particles::addParticle(float x, float y, int color)
{
    m_xPositions.push_back(x);
    m_yPositions.push_back(y);
    m_xVelocity.push_back(0.0f);
    m_yVelocity.push_back(0.0f);
    m_colors.push_back(color);
}

void particles::clear()
{
    m_xPositions.clear();
    m_yPositions.clear();
    m_xVelocity.clear();
    m_yVelocity.clear();
    m_colors.clear();
}

size_t particles::size() { return m_xPositions.size(); }

[[nodiscard]] const std::vector<float> &particles::getXPositions() const { return m_xPositions; }
[[nodiscard]] const std::vector<float> &particles::getYPositions() const { return m_yPositions; }
[[nodiscard]] const std::vector<int> &particles::getColors() const { return m_colors; }

void particles::wrapAround(float Width, float Height)
{
    for (float &m_xPosition: m_xPositions)
    {
        if (m_xPosition < 0) { m_xPosition += Width; }
        else if (m_xPosition >= Width) { m_xPosition -= Width; }
    }

    for (float &m_yPosition: m_yPositions)
    {
        if (m_yPosition < 0) { m_yPosition += Height; }
        else if (m_yPosition >= Height) { m_yPosition -= Height; }
    }
}
