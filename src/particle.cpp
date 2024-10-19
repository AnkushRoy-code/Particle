#include "particle.h"

#include "color.h"

#include <SDL.h>
#include <SDL_timer.h>
#include <cmath>

//---------------------------------------------------------------------------
// Local Values
//---------------------------------------------------------------------------

// this is the width of the control pannel every particle is displaced this
// amount of distance to the right of the screen so they don't overlap.

//---------------------------------------------------------------------------
// Implementation Of Functions
//---------------------------------------------------------------------------
particle::particle(float x, float y, int color) :
    m_x(x), m_y(y), m_vx(0), m_vy(0), m_color(color)
{
}

// this is the main logic of the particle simulation. This.... this function has
// the most maths/Physics that I implemented in this project, I knew the logic
// that I had to put here by other people that had made it or showcased it. But
// imblementating what I know in cpp was not as easy as it seemed, this function
// went through a lot of changes throughout the days.
void particle::update(const std::vector<particle> &Particles,
                      float Width,
                      float Height,
                      double deltaTime,
                      float Force[COLOR_COUNT][COLOR_COUNT],
                      int MinDistance[COLOR_COUNT][COLOR_COUNT],
                      int MaxDistance[COLOR_COUNT][COLOR_COUNT],
                      int ImGuiWindowWidth)
{
    m_ImGuiWindowWidth = ImGuiWindowWidth;

    float halfWidth  = 0.5f * Width;
    float halfHeight = 0.5f * Height;

    for (const auto &other: Particles)
    {
        // skip calculating force with itself.
        if (&other == this) continue;

        float dx = other.getPosX() - m_x;
        float dy = other.getPosY() - m_y;

        // these 4 if statements are so that the particle force wrap around. Not
        // the particle itself. There's another function that does it later in
        // this same function.
            if (dx > halfWidth) { dx -= Width; }
            else if (dx < -halfWidth) { dx += Width; }

            if (dy > halfHeight) { dy -= Height; }
            else if (dy < -halfHeight) { dy += Height; }

        // calculate distance between the 2 particles.
        float distance =
            std::hypot(dx, dy);  // hypot does this: (x*x + y*y)^0.5 since it
                                 // is a inbuilt function i decided to use it.

        float force = 0.0f;

        // the user sets the min/max distances
        if (distance < MinDistance[m_color][other.m_color]) { force = -1.0f; }
        else if (distance <= MaxDistance[m_color][other.m_color])
        {
            force = Force[m_color][other.m_color];
        }

        float invDistance = 1.2f * distance;
        float fx          = force * (dx / invDistance);
        float fy          = force * (dy / invDistance);

        m_vx += fx;
        m_vy += fy;
    }

    // you gotta multiply everyting with deltaTime.
    m_x += m_vx * deltaTime;
    m_y += m_vy * deltaTime;

    m_vx *= 0.95f;
    m_vy *= 0.95f;

    // this wrap arounds the particle position itself if it goes out of bounds.
     wrapAround(Width, Height);
}

// i wonder what they do ...
float particle::getPosX() const { return m_x; }
float particle::getPosY() const { return m_y; }

void particle::wrapAround(float Width, float Height)
{
    if (m_x < 0) { m_x += Width; }
    else if (m_x >= Width) { m_x -= Width; }
    if (m_y < 0) { m_y += Height; }
    else if (m_y >= Height) { m_y -= Height; }
}

