#include "SDL.h"
#pragma once

class particle {
public:
  void drawParticle(SDL_Renderer *renderer, float x, float y);
  void updateParticle(SDL_Renderer *Renderer);
  void initialiseParticles();

private:
  float x, y, speedx, speedy;
};
