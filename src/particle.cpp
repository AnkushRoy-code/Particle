#include "particle.h"
#include "color.h"
#include <SDL.h>
#include <SDL_timer.h>
#include <cmath>
#include <omp.h>

//---------------------------------------------------------------------------
// Local Values
//---------------------------------------------------------------------------

// this is the width of the control pannel every particle is displaced this
// amount of distance to the right of the screen so they don't overlap.

const SDL_Color ColorMap[COLOR_COUNT] = {
    {255, 0, 0, 255},     // RED
    {0, 255, 0, 255},     // GREEN
    {0, 0, 255, 255},     // BLUE
    {255, 255, 255, 255}, // WHITE
    {255, 255, 25, 255},  // YELLOW
    {145, 30, 180, 255},  // PURPLE
    {70, 240, 240, 255},  // CYAN
    {240, 50, 230, 255}   // MAGENTA
};
//---------------------------------------------------------------------------
// Implementation Of Functions
//---------------------------------------------------------------------------
particle::particle(float x, float y, int color)
    : x(x), y(y), vx(0), vy(0), color(color) {}

// for particle radius > 1 calculate the rect wrt particle position and then
// render the rect.
void particle::drawParticle(SDL_Renderer *Renderer, int Radius, float Scale,
                            float OffSetX, float OffSetY) const {
  SDL_Color col = ColorMap[color];
  SDL_SetRenderDrawColor(Renderer, col.r, col.g, col.b, col.a);

  // a very special magical formulae I made to calculating rect.
  SDL_Rect rect = calcParticleSize(Radius, Scale, OffSetX, OffSetY);
  SDL_RenderFillRect(Renderer, &rect);
}

// this is the main logic of the particle simulation.
void particle::update(const std::vector<particle> &Particles, float Width,
                      float Height, double deltaTime,
                      float Force[COLOR_COUNT][COLOR_COUNT],
                      int MinDistance[COLOR_COUNT][COLOR_COUNT],
                      int MaxDistance[COLOR_COUNT][COLOR_COUNT],
                      int ImGuiWindowWidth, bool Wrap) {

  pImGuiWindowWidth = ImGuiWindowWidth;

  float halfWidth = 0.5f * Width;
  float halfHeight = 0.5f * Height;

#pragma omp parallel for
  for (const auto &other : Particles) {
    // skip calculating force with itself.
    if (&other == this)
      continue;

    float dx = other.getPosX() - x;
    float dy = other.getPosY() - y;

    // these 4 if statements are so that the particle force wrap around. Not the
    // particle itself. There's another function that does it later in this same
    // function.
    if (Wrap) {
      if (dx > halfWidth) {
        dx -= Width;
      } else if (dx < -halfWidth) {
        dx += Width;
      }

      if (dy > halfHeight) {
        dy -= Height;
      } else if (dy < -halfHeight) {
        dy += Height;
      }
    }

    // calculate distance between the 2 particles.
    float distance =
        std::hypot(dx, dy); // hypot does this: (x*x + y*y)^0.5 since it is
                            // a inbuilt function i decided to use it.

    float force = 0.0f;

    // the user sets the min/max distances
    if (distance < MinDistance[color][other.color]) {
      force = -1.0f;
    } else if (distance <= MaxDistance[color][other.color]) {
      force = Force[color][other.color];
    }

    float invDistance = 1.2f * distance;
    float fx = force * (dx / invDistance);
    float fy = force * (dy / invDistance);

    vx += fx;
    vy += fy;
  }

  // you gotta multiply everyting with deltaTime.
  x += vx * deltaTime;
  y += vy * deltaTime;

  vx *= 0.95f;
  vy *= 0.95f;

  // this wrap arounds the particle position itself if it goes out of bounds.
  if (Wrap) {
    wrapAround(Width, Height);
  } else {
    dontWrapAround(Width, Height);
  }
}

// i wonder what they do ...
float particle::getPosX() const { return x; }
float particle::getPosY() const { return y; }

// calculate the particle rect size.
SDL_Rect particle::calcParticleSize(int Radius, float Scale, float OffSetX,
                                    float OffSetY) const {
  SDL_Rect rect;
  if (Radius % 2 == 0) {
    // x or y - r*s/2 -1
    rect.x = static_cast<int>((x * Scale) + OffSetX) - ((Radius / 2) - 1) +
             pImGuiWindowWidth;
    rect.y = static_cast<int>((y * Scale) + OffSetY) + ((Radius / 2) - 1);
  } else {
    rect.x = (static_cast<int>((x * Scale) + OffSetX) - ((Radius - 1) / 2)) +
             pImGuiWindowWidth;
    rect.y = static_cast<int>((y * Scale) + OffSetY) + ((Radius - 1) / 2);
  }

  if (static_cast<int>(Radius * Scale) <= 0) {
    rect.h = rect.w = 1;
  } else {
    rect.h = rect.w = static_cast<int>(Radius * Scale);
  }
  return rect;
}

void particle::wrapAround(float Width, float Height) {
  if (x < 0) {
    x += Width;
  } else if (x >= Width) {
    x -= Width;
  }
  if (y < 0) {
    y += Height;
  } else if (y >= Height) {
    y -= Height;
  }
}

void particle::dontWrapAround(float Width, float Height) {
  if (x < 0) {
    x = 0;
  } else if (x > Width - 2) {
    x = Width - 2;
  }
  if (y < 0) {
    y = 0;
  } else if (y > Height - 4) {
    y = Height - 4;
  }
}
