#include "particle.h"
#include "color.h"
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_timer.h>

const int DISPLACE = 360;

particle::particle(float x, float y, int color)
    : x(x), y(y), vx(0), vy(0), color(color) {}

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

// for particles with radius > 1
void particle::drawParticle(SDL_Renderer *Renderer, int Radius) const {
  SDL_Color col = ColorMap[color];
  SDL_SetRenderDrawColor(Renderer, col.r, col.g, col.b, col.a);

  SDL_Rect rect = calcParticleSize(Radius);
  SDL_RenderFillRect(Renderer, &rect);
}

// for particle radius < 1
void particle::drawParticlePoint(SDL_Renderer *Renderer) const {
  SDL_Color col = ColorMap[color];
  SDL_SetRenderDrawColor(Renderer, col.r, col.g, col.b, col.a);
  SDL_RenderDrawPoint(Renderer, x + DISPLACE, y);
}

void particle::update(const std::vector<particle> &Particles, float Width,
                      float Height, double deltaTime, int Radius,
                      float Force[COLOR_COUNT][COLOR_COUNT],
                      int MinDistance[COLOR_COUNT][COLOR_COUNT],
                      int MaxDistance[COLOR_COUNT][COLOR_COUNT]) {

  for (const auto &other : Particles) {
    if (&other == this)
      continue;

    float dx = other.getPosX() - x;
    float dy = other.getPosY() - y;

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
    float distance = std::hypot(dx, dy);

    float force = 0.0f;

    if (distance < Radius * 3.0f) {
      force = -1.0f;
    } else if (distance <= 300) {
      force = Force[color][other.color];
    }

    float fx = force * (dx / (1.2 * distance));
    float fy = force * (dy / (1.2 * distance));

    vx += fx;
    vy += fy;
  }

  x += vx * deltaTime;
  y += vy * deltaTime;

  vx *= 0.95f;
  vy *= 0.95f;

  wrapAround(Width, Height);
}

SDL_Rect particle::calcParticleSize(int Radius) const {
  SDL_Rect rect;
  if (Radius == 1) {
    rect.x = static_cast<int>(x) + DISPLACE;
    rect.y = static_cast<int>(y);
  } else if (Radius % 2 == 0) {
    rect.x = (static_cast<int>(x) - ((Radius / 2) - 1)) + DISPLACE;
    rect.y = static_cast<int>(y) + ((Radius / 2) - 1);
  } else {
    rect.x = (static_cast<int>(x) - ((Radius - 1) / 2)) + DISPLACE;
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

void particle::setForce(int ColorA, int ColorB, float Value) {
  force[ColorA][ColorB] = Value;
}

int particle::getColor() const { return color; }
float particle::getPosX() const { return x; }
float particle::getPosY() const { return y; }
