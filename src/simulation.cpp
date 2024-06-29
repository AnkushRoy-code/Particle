#include "simulation.h"

#include <cstdlib>

Simulation::Simulation(int width, int height) : width(width), height(height) {}

void Simulation::initialize(int particleCount) {
  particles.clear();
  for (int i = 0; i < particleCount; ++i) {
    float x = static_cast<float>(rand() % width);
    float y = static_cast<float>(rand() % height);
    int color = rand() % 3; // Three possible colors: 0, 1, 2
    particles.emplace_back(x, y, color);
  }
}

void Simulation::update() {
  for (auto &particle : particles) {
    particle.update(particles, width, height);
  }
}

const std::vector<particle> &Simulation::getParticles() const {
  return particles;
}
