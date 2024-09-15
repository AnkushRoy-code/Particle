#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include "backends/imgui_impl_sdl2.h"

class inputHandler
{
  private:
    SDL_Event event;

  public:
    void processEvents(SDL_Window *Window,
                       float &Scale,
                       bool &MiddleMouseButtonPressed,
                       float &MouseStartPanX,
                       float &MouseStartPanY,
                       float &OffsetX,
                       float &OffsetY,
                       float &OffsetEndX,
                       float &OffsetEndY,
                       bool &Quit);

    void handleMouseMotion(bool middleMouseButtonPressed,
                           float scale,
                           float mouseStartPanX,
                           float mouseStartPanY,
                           float &OffsetX,
                           float &OffsetY,
                           float &OffsetEndX,
                           float &OffsetEndY);

  private:
    void adjustScale(float &Scale);
    void handleMouseButtonDown(bool &MiddleMouseButtonPressed,
                               float &MouseStartPanX,
                               float &MouseStartPanY,
                               float scale);
    void handleMouseButtonUp(bool &MiddleMouseButtonPressed,
                             float &OffsetX,
                             float &OffsetY,
                             float &OffsetEndX,
                             float &OffsetEndY);
    void handleKeyDown(
        float &Scale, float &OffsetX, float &OffsetY, float &OffsetEndX, float &OffsetEndY);
};
