#pragma once

#include "color.h"
#include "particle.h"
#include <SDL.h>
#include <imgui.h>
#include <vector>

class UI {
public:
  UI(int Width, int Height);
  void initializeParticle(int ParticleCount, int NumOfParticleColor);
  void initialize(SDL_Window *window, SDL_Renderer *renderer);
  bool setup();
  void close();
  void update(SDL_Renderer *renderer, double DeltaTime);
  void updateParticle(double DeltaTime);

  const std::vector<particle> &getParticles() const;

  void renderParticle(SDL_Renderer *Renderer);
  void setRadius(int Radius);

  void checkBool(int start, int end, const char *string);
  void populateRandomForce();
  void resetForce();
  void defaultForce();
  void setDefaultForce();

  void populateRandomMinDistance();
  void resetMinDistance();
  void defaultMinDistance();
  void setDefaultMinDistance();

  void populateRandomMaxDistance();
  void resetMaxDistance();
  void defaultMaxDistance();
  void setDefaultMaxDistance();

  void createColorTreeNode(const char *label, int colorIndex);
  void createMinDistTreeNode(const char *label, int colorIndex);
  void createMaxDistTreeNode(const char *label, int colorIndex);
  void showColorSliders();
  void showMinDistSliders();
  void showMaxDistSliders();
  void printForce();

private:
  bool showDemoWindow = true;
  int width, height;

  int radius = 3;
  int particleCount = 100, numOfParticleColor = 4;
  std::vector<particle> particles;

  double deltaTime;

  // initial value
  float defaultForceValue[COLOR_COUNT][COLOR_COUNT] = {
      // RED GREEN BLUE WHITE YELLOW PURPLE CYAN MAGENTA

      {-0.25f, 0.5f, 0, 0, 0, 0, 0, 0}, // RED,
      {0, -0.25f, 0.5f, 0, 0, 0, 0, 0}, // GREEN,
      {0, 0, -0.25f, 0.5f, 0, 0, 0, 0}, // BLUE,
      {0.5f, 0, 0, -0.25f, 0, 0, 0, 0}, // WHITE,
      {0, 0, 0, 0, 0, 0, 0, 0},         // YELLOW,
      {0, 0, 0, 0, 0, 0, 0, 0},         // PURPLE,
      {0, 0, 0, 0, 0, 0, 0, 0},         // CYAN,
      {0, 0, 0, 0, 0, 0, 0, 0}          // MAGENTA,
  };
  int defaultMinDistanceValue[COLOR_COUNT][COLOR_COUNT] = {
      // RED GREEN BLUE WHITE YELLOW PURPLE CYAN MAGENTA

      {3, 5, 0, 0, 0, 0, 0, 0}, // RED,
      {0, 2, 5, 0, 0, 0, 0, 0}, // GREEN,
      {0, 0, 2, 5, 0, 0, 0, 0}, // BLUE,
      {5, 0, 0, 2, 0, 0, 0, 0}, // WHITE,
      {0, 0, 0, 0, 0, 0, 0, 0}, // YELLOW,
      {0, 0, 0, 0, 0, 0, 0, 0}, // PURPLE,
      {0, 0, 0, 0, 0, 0, 0, 0}, // CYAN,
      {0, 0, 0, 0, 0, 0, 0, 0}  // MAGENTA,
  };
  int defaultMaxDistanceValue[COLOR_COUNT][COLOR_COUNT] = {
      // RED GREEN BLUE WHITE YELLOW PURPLE CYAN MAGENTA

      {300, 250, 0, 0, 0, 0, 0, 0}, // RED,
      {0, 200, 250, 0, 0, 0, 0, 0}, // GREEN,
      {0, 0, 200, 500, 0, 0, 0, 0}, // BLUE,
      {5, 0, 0, 200, 0, 0, 0, 0},   // WHITE,
      {0, 0, 0, 0, 0, 0, 0, 0},     // YELLOW,
      {0, 0, 0, 0, 0, 0, 0, 0},     // PURPLE,
      {0, 0, 0, 0, 0, 0, 0, 0},     // CYAN,
      {0, 0, 0, 0, 0, 0, 0, 0}      // MAGENTA,
  };

  float Force[COLOR_COUNT][COLOR_COUNT];
  int minDist[COLOR_COUNT][COLOR_COUNT];
  int maxDist[COLOR_COUNT][COLOR_COUNT];
};
