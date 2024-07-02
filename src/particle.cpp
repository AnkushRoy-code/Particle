#include "particle.h"
#include "color.h"
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_timer.h>

const int DISPLACE = 360;

particle::particle(float x, float y, int color)
    : x(x), y(y), vx(0), vy(0), color(color) {}

void particle::drawParticle(SDL_Renderer *Renderer, int Radius) const {
  switch (color) {
  case RED:
    SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
    break; // Red
  case GREEN:
    SDL_SetRenderDrawColor(Renderer, 0, 255, 0, 255);
    break; // Green
  case BLUE:
    SDL_SetRenderDrawColor(Renderer, 0, 0, 255, 255);
    break; // Blue
  case WHITE:
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    break;
  case YELLOW:
    SDL_SetRenderDrawColor(Renderer, 255, 255, 25, 255);
    break;
  case PURPLE:
    SDL_SetRenderDrawColor(Renderer, 145, 30, 180, 255);
    break;
  case CYAN:
    SDL_SetRenderDrawColor(Renderer, 70, 240, 240, 255);
    break;
  case MAGENTA:
    SDL_SetRenderDrawColor(Renderer, 240, 50, 230, 255);
    break;
  }
  SDL_Rect rect = calcParticleSize(Radius);
  SDL_RenderFillRect(Renderer, &rect);
}

void particle::drawParticlePoint(SDL_Renderer *Renderer) const {
  switch (color) {
  case RED:
    SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
    break;
  case GREEN:
    SDL_SetRenderDrawColor(Renderer, 0, 255, 0, 255);
    break;
  case BLUE:
    SDL_SetRenderDrawColor(Renderer, 0, 0, 255, 255);
    break;
  case WHITE:
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    break;
  case YELLOW:
    SDL_SetRenderDrawColor(Renderer, 255, 255, 25, 255);
    break;
  case PURPLE:
    SDL_SetRenderDrawColor(Renderer, 145, 30, 180, 255);
    break;
  case CYAN:
    SDL_SetRenderDrawColor(Renderer, 70, 240, 240, 255);
    break;
  case MAGENTA:
    SDL_SetRenderDrawColor(Renderer, 240, 50, 230, 255);
    break;
  }
  SDL_RenderDrawPoint(Renderer, x + DISPLACE, y);
}

void particle::update(const std::vector<particle> &Particles, float Width,
                      float Height, double deltaTime, int Radius,
                      float Force[COLOR_COUNT][COLOR_COUNT]) {
  for (const auto &other : Particles) {
    if (&other == this)
      continue;

    float dx = other.getPosX() - x;
    float dy = other.getPosY() - y;
    float distance = std::sqrt(dx * dx + dy * dy);

    bool tooClose = false;
    bool tooFar = false;

    float force = 0.0f;
    if (distance < Radius * 1.5) {
      force = -1.0f;
      tooClose = true;
    } else {
      tooClose = false;
    }
    if (distance > 300) {
      tooFar = true;
    } else {
      tooFar = false;
    }

    if (!tooClose && !tooFar) {
      force = Force[color][other.color];
    }

    float fx = force * (dx / distance);
    float fy = force * (dy / distance);

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
