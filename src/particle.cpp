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

const SDL_Color ColorMap[COLOR_COUNT] = {
    {255, 0, 0, 255},      // RED
    {0, 255, 0, 255},      // GREEN
    {0, 0, 255, 255},      // BLUE
    {255, 255, 255, 255},  // WHITE
    {255, 255, 25, 255},   // YELLOW
    {145, 30, 180, 255},   // PURPLE
    {70, 240, 240, 255},   // CYAN
    {240, 50, 230, 255}    // MAGENTA
};
//---------------------------------------------------------------------------
// Implementation Of Functions
//---------------------------------------------------------------------------
particle::particle(float x, float y, int color) :
    m_x(x), m_y(y), m_vx(0), m_vy(0), m_color(color)
{
}

// for particle radius > 1 calculate the rect wrt particle position and then
// render the rect.
void particle::drawParticle(SDL_Renderer *Renderer,
                            int Radius,
                            float Scale,
                            float OffSetX,
                            float OffSetY) const
{
    SDL_Color col = ColorMap[m_color];
    SDL_SetRenderDrawColor(Renderer, col.r, col.g, col.b, col.a);

    // a very special magical formulae I made to calculating rect.
    SDL_Rect rect = calcParticleSize(Radius, Scale, OffSetX, OffSetY);
    SDL_RenderFillRect(Renderer, &rect);
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
                      int ImGuiWindowWidth,
                      bool Wrap)
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
        if (Wrap)
        {
            if (dx > halfWidth) { dx -= Width; }
            else if (dx < -halfWidth) { dx += Width; }

            if (dy > halfHeight) { dy -= Height; }
            else if (dy < -halfHeight) { dy += Height; }
        }

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
    if (Wrap) { wrapAround(Width, Height); }
    else { dontWrapAround(Width, Height); }
}

// i wonder what they do ...
float particle::getPosX() const { return m_x; }
float particle::getPosY() const { return m_y; }

// calculate the particle rect size.
SDL_Rect particle::calcParticleSize(int Radius,
                                    float Scale,
                                    float OffSetX,
                                    float OffSetY) const
{
    SDL_Rect rect;
    if (Radius % 2 == 0)
    {
        // x or y - r*s/2 -1
        rect.x = static_cast<int>((m_x * Scale) + OffSetX) - ((Radius / 2) - 1)
                 + m_ImGuiWindowWidth;
        rect.y = static_cast<int>((m_y * Scale) + OffSetY) + ((Radius / 2) - 1);
    }
    else
    {
        rect.x =
            (static_cast<int>((m_x * Scale) + OffSetX) - ((Radius - 1) / 2))
            + m_ImGuiWindowWidth;
        rect.y = static_cast<int>((m_y * Scale) + OffSetY) + ((Radius - 1) / 2);
    }

    if (static_cast<int>(Radius * Scale) <= 0) { rect.h = rect.w = 1; }
    else { rect.h = rect.w = static_cast<int>(Radius * Scale); }
    return rect;
}

void particle::wrapAround(float Width, float Height)
{
    if (m_x < 0) { m_x += Width; }
    else if (m_x >= Width) { m_x -= Width; }
    if (m_y < 0) { m_y += Height; }
    else if (m_y >= Height) { m_y -= Height; }
}

void particle::dontWrapAround(float Width, float Height)
{
    if (m_x < 0) { m_x = 0; }
    else if (m_x > Width - 2) { m_x = Width - 2; }
    if (m_y < 0) { m_y = 0; }
    else if (m_y > Height - 4) { m_y = Height - 4; }
}
