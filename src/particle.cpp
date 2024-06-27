#include "particle.h"
#include <SDL.h>

void particle::drawParticle(SDL_Renderer *renderer, float x, float y) {
  SDL_RenderDrawPoint(renderer, x, y);
}

void particle::updateParticle(SDL_Renderer *Renderer) {
  for (int i = 0; i < 100; i++) {
    SDL_RenderDrawPoint(Renderer, i, i);
  }
}
