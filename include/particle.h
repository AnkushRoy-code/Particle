#pragma once

#include <SDL.h>
#include <vector>

class particle {
public:
  particle(float X, float Y, int Color);
  void drawParticle(SDL_Renderer *Renderer) const;
  void update(const std::vector<particle> &Particles, float Width,
              float Height);
  float getPosX() const;
  float getPosY() const;
  int getColor() const;
  float setPosX();
  float setPosY();
  float setSpeedX();
  float setSpeedY();

private:
  float x, y, vx, vy;
  int radius = 3;
  int color;

private:
  SDL_Rect calcParticleSize() const;
  void wrapAround(float Width, float Height);
};
