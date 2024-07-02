#pragma once

#include "color.h"
#include <SDL.h>
#include <vector>

class particle {
public:
  particle(float X, float Y, int Color);
  void drawParticle(SDL_Renderer *Renderer, int Radius) const;
  void drawParticlePoint(SDL_Renderer *Renderer) const;
  void update(const std::vector<particle> &Particles, float Width, float Height,
              double deltaTime, int Radius,
              float Force[COLOR_COUNT][COLOR_COUNT]);

  float getPosX() const;
  float getPosY() const;
  int getColor() const;

  void setForce(int ColorA, int ColorB, float Value);
  // int getForce(int ColorA, int ColorB);

private:
  float x, y, vx, vy;
  int color;

  // Force setup
  // Colors -> Red(0), Green(1), Blue(2), White(3),
  // Yellow(4), Purple(5), Cyan(6), Magenta(7)

  float force[COLOR_COUNT][COLOR_COUNT];

private:
  SDL_Rect calcParticleSize(int Radius) const;
  void wrapAround(float Width, float Height);
};
