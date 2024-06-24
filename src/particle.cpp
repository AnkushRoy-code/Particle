#include "particle.h"
#include <SDL.h>

void particle::drawParticle(SDL_Renderer *renderer, float x, float y) {
  SDL_RenderDrawPoint(renderer, x, y);
}

void particle::updateParticle() {
  x += speedx;
  y += speedy;
}
