#pragma once

#include "particle.h"

#include <SDL_render.h>
#include <vector>

class Simulation {

public:
  Simulation(int width, int height);

  void initialize(int particleCount);
  void update();

  const std::vector<particle> &getParticles() const;

  void render(SDL_Renderer *renderer) {
    const auto &particles = getParticles();
    for (const auto &particle : particles) {
      particle.drawParticle(renderer);
    }
  }

private:
  int width, height;
  std::vector<particle> particles;
};
