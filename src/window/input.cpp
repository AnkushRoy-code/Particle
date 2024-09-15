#include "window/input.h"
#include "window/input.h"

void inputHandler::processEvents(SDL_Window *Window,
                                 float &Scale,
                                 bool &MiddleMouseButtonPressed,
                                 float &MouseStartPanX,
                                 float &MouseStartPanY,
                                 float &OffsetX,
                                 float &OffsetY,
                                 float &OffsetEndX,
                                 float &OffsetEndY,
                                 bool &Quit)
{
    SDL_Event event;  // Create a local event object

    while (SDL_PollEvent(&event) != 0)
    {
        ImGui_ImplSDL2_ProcessEvent(&event);

        if (event.type == SDL_KEYDOWN)
        {
            handleKeyDown(Scale, OffsetX, OffsetY, OffsetEndX, OffsetEndY);
        }
        else if (event.type == SDL_QUIT) { Quit = true; }

        else if (event.type == SDL_WINDOWEVENT
                 && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
            int w {}, h {};
            SDL_GetWindowSize(Window, &w, &h);
            glViewport(0, 0, w, h);
        }

        if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) || ImGui::IsAnyItemHovered())
        {
            continue;
        }

        switch (event.type)
        {
            case SDL_MOUSEWHEEL: adjustScale(Scale); break;

            case SDL_MOUSEBUTTONDOWN:
                handleMouseButtonDown(MiddleMouseButtonPressed, MouseStartPanX, MouseStartPanY,
                                      Scale);
                break;

            case SDL_MOUSEBUTTONUP:
                handleMouseButtonUp(MiddleMouseButtonPressed, OffsetX, OffsetY, OffsetEndX,
                                    OffsetEndY);
                break;

            default: break;
        }
    }
}
void inputHandler::adjustScale(float &Scale)
{

    if (event.wheel.y > 0) { Scale *= 1.05f; }
    else if (event.wheel.y < 0) { Scale *= 0.95f; }
}

void inputHandler::handleMouseButtonDown(bool &middleMouseButtonPressed,
                                         float &mouseStartPanX,
                                         float &mouseStartPanY,
                                         float scale)
{
    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        middleMouseButtonPressed = true;
        int x, y;
        SDL_GetMouseState(&x, &y);
        mouseStartPanX = x / scale;
        mouseStartPanY = y / scale;
    }
}

void inputHandler::handleMouseButtonUp(bool &middleMouseButtonPressed,
                                       float &offsetX,
                                       float &offsetY,
                                       float &offsetEndX,
                                       float &offsetEndY)
{
    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        middleMouseButtonPressed = false;
        offsetEndX               = offsetX;
        offsetEndY               = offsetY;
    }
}

void inputHandler::handleKeyDown(
    float &scale, float &offsetX, float &offsetY, float &offsetEndX, float &offsetEndY)
{
    switch (event.key.keysym.sym)
    {
        case SDLK_m: offsetX = offsetY = offsetEndX = offsetEndY = 0.0f; break;

        case SDLK_z: scale = 1.0f; break;

        default: break;
    }
}

void inputHandler::handleMouseMotion(bool middleMouseButtonPressed,
                                     float scale,
                                     float mouseStartPanX,
                                     float mouseStartPanY,
                                     float &offsetX,
                                     float &offsetY,
                                     float &offsetEndX,
                                     float &offsetEndY)
{
    if (middleMouseButtonPressed)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        offsetY = offsetEndY + ((y / scale) - mouseStartPanY);
        offsetX = offsetEndX + ((x / scale) - mouseStartPanX);
    }
}
