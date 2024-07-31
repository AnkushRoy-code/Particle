#include "particle.h"
#include "color.h"
#include <SDL.h>
#include <SDL_timer.h>

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
void particle::drawParticle(SDL_Renderer *Renderer, int Radius) const {
  SDL_Color col = ColorMap[color];
  SDL_SetRenderDrawColor(Renderer, col.r, col.g, col.b, col.a);

  SDL_Rect rect = calcParticleSize(
      Radius); // a very special magical formulae I made to calculating rect.
  SDL_RenderFillRect(Renderer, &rect);
}

// for particles with radius < 1 just draw a point instead of calculating the
// rect and then rendering it.
void particle::drawParticlePoint(SDL_Renderer *Renderer) const {
  SDL_Color col = ColorMap[color];
  SDL_SetRenderDrawColor(Renderer, col.r, col.g, col.b, col.a);
  SDL_RenderDrawPoint(Renderer, x + private_ImGuiWindowWidth, y);
}

// this is the main logic of the particle simulation.
void particle::update(const std::vector<particle> &Particles, float Width,
                      float Height, double deltaTime,
                      float Force[COLOR_COUNT][COLOR_COUNT],
                      int MinDistance[COLOR_COUNT][COLOR_COUNT],
                      int MaxDistance[COLOR_COUNT][COLOR_COUNT],
                      int ImGuiWindowWidth) {

  private_ImGuiWindowWidth = ImGuiWindowWidth;
  for (const auto &other : Particles) {
    // skip calculating force with itself.
    if (&other == this)
      continue;

    float dx = other.getPosX() - x;
    float dy = other.getPosY() - y;

    // these 4 if statements are so that the particle force wrap around. Not the
    // particle itself. There's another function that does it later in this same
    // function.
    if (dx > 0.5 * Width) {
      dx = dx - Width;
    }
    if (dx < -0.5 * Width) {
      dx = dx + Width;
    }
    if (dy > 0.5 * Height) {
      dy = dy - Height;
    }
    if (dy < -0.5 * Height) {
      dy = dy + Height;
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

    float fx = force * (dx / (1.2 * distance));
    float fy = force * (dy / (1.2 * distance));

    vx += fx;
    vy += fy;
  }

  // you gotta multiply everyting with deltaTime.
  x += vx * deltaTime;
  y += vy * deltaTime;

  vx *= 0.95f;
  vy *= 0.95f;

  // this wrap arounds the particle position itself if it goes out of bounds.
  wrapAround(Width, Height);
}

// i wonder what they do ...
float particle::getPosX() const { return x; }
float particle::getPosY() const { return y; }

// calculate the particle rect size.
SDL_Rect particle::calcParticleSize(int Radius) const {
  SDL_Rect rect;
  if (Radius == 1) {
    rect.x = static_cast<int>(x) + private_ImGuiWindowWidth;
    rect.y = static_cast<int>(y);
  } else if (Radius % 2 == 0) {
    rect.x =
        (static_cast<int>(x) - ((Radius / 2) - 1)) + private_ImGuiWindowWidth;
    rect.y = static_cast<int>(y) + ((Radius / 2) - 1);
  } else {
    rect.x =
        (static_cast<int>(x) - ((Radius - 1) / 2)) + private_ImGuiWindowWidth;
    rect.y = static_cast<int>(y) + ((Radius - 1) / 2);
  }
  rect.h = rect.w = Radius;
  return rect;
}

void particle::wrapAround(float Width, float Height) {
  if (x < 0) {
    x += Width;
  }
  if (x >= Width) {
    x -= Width;
  }
  if (y < 0) {
    y += Height;
  }
  if (y >= Height) {
    y -= Height;
  }
}
