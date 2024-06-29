#include "particle.h"
#include <SDL.h>
#include <SDL_timer.h>

particle::particle(float x, float y, int color)
    : x(x), y(y), vx(0), vy(0), color(color) {}
void particle::drawParticle(SDL_Renderer *Renderer) const {
  switch (color) {
  case 0:
    SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
    break; // Red
  case 1:
    SDL_SetRenderDrawColor(Renderer, 0, 255, 0, 255);
    break; // Green
  case 2:
    SDL_SetRenderDrawColor(Renderer, 0, 0, 255, 255);
    break; // Blue
  }
  SDL_Rect rect = calcParticleSize();
  SDL_RenderFillRect(Renderer, &rect);
}

void particle::update(const std::vector<particle> &Particles, float Width,
                      float Height) {
  for (const auto &other : Particles) {
    if (&other == this)
      continue;
    float dx = other.getPosX() - x;
    float dy = other.getPosY() - y;
    float distance = std::sqrt(dx * dx + dy * dy);
    if (distance < radius + 1) {
      continue;
    }
    // Calculate force (simple attraction/repulsion logic)
    float force = 0.0f;
    if (color == 0 && other.getColor() == 1) {
      force = 0.2f;
    } else if (color == 1 && other.getColor() == 0) {
      force = 0.3f;
    } else if (color == 2 && other.getColor() == 1) {
      force = 0.01f;
    } else if (color == 2 && other.getColor() == 2) {
      force = -0.4;
    }
    float fx = force * (dx / distance);
    float fy = force * (dy / distance);
    vx += fx;
    vy += fy;
  }
  x += vx;
  y += vy;
  vx *= 0.95f;
  vy *= 0.95f;
  wrapAround(Width, Height);
}

const int DISPLACE = 360;
SDL_Rect particle::calcParticleSize() const {
  SDL_Rect rect;
  if (radius == 1) {
    rect.x = static_cast<int>(x) + DISPLACE;
    rect.y = static_cast<int>(y);
  } else if (radius % 2 == 0) {
    rect.x = (static_cast<int>(x) - ((radius / 2) - 1)) + DISPLACE;
    rect.y = static_cast<int>(y) + ((radius / 2) - 1);
  } else {
    rect.x = (static_cast<int>(x) - ((radius - 1) / 2)) + DISPLACE;
    rect.y = static_cast<int>(y) + ((radius - 1) / 2);
  }
  rect.h = rect.w = radius;
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

int particle::getColor() const { return color; }
float particle::getPosX() const { return x; }
float particle::getPosY() const { return y; }
