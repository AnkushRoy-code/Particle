#include "App.h"

#include "SDLstuff.h"
#include "UI.h"

#include <SDL.h>
#include <iostream>
#include <backends/imgui_impl_sdl2.h>

//---------------------------------------------------------------------------
//  Local Things
//---------------------------------------------------------------------------

// These are for deltaTime
Uint64 currentTick = SDL_GetPerformanceFrequency();
Uint64 lastTick    = 0;
double deltaTime   = 0;

// These are for capping fps because my monitor doesn't even support more
// than 60.
const int FPS        = 60;
const int frameDelay = 1000 / FPS;
Uint32 frameStart;
int frameTime;

void calcDeltatime()
{
    lastTick    = currentTick;
    currentTick = SDL_GetPerformanceCounter();
    deltaTime   = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());
}

//---------------------------------------------------------------------------
// Implementation Of functions
//---------------------------------------------------------------------------
bool App::initialize()
{
    m_SDLStuff.initialise(m_window, m_renderer);

    if (m_window == nullptr)
    {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (m_renderer == nullptr)
    {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    int h, w;
    SDL_GetWindowSize(m_window, &w, &h);

    m_UI.initialize(m_window, m_renderer, w, h);
    // IDK how to check if imgui was successfully initialised.
    return true;
}

void App::update(float Scale, float offSetX, float offSetY)
{
    m_UI.setup();
    m_UI.update(m_window, m_renderer, deltaTime, Scale, offSetX, offSetY);

    int h, w;
    SDL_GetWindowSize(m_window, &w, &h);

    m_UI.setSize(w, h);
}

void App::render() { SDL_RenderPresent(m_renderer); }

void App::close()
{
    m_UI.close();
    m_SDLStuff.close(m_window, m_renderer);
}

void App::processEvents(SDL_Event &event,
                        float &scale,
                        bool &middleMouseButtonPressed,
                        float &mouseStartPanX,
                        float &mouseStartPanY,
                        float &offsetX,
                        float &offsetY,
                        float &offsetEndX,
                        float &offsetEndY,
                        bool &quit)
{
    while (SDL_PollEvent(&event) != 0)
    {
        ImGui_ImplSDL2_ProcessEvent(&event);

        // Always process keyboard and exit events
        if (event.type == SDL_KEYDOWN)
        {
            handleKeyDown(event, scale, offsetX, offsetY, offsetEndX, offsetEndY);
        }
        else if (event.type == SDL_QUIT) { quit = true; }

        // Skip handling mouse events if ImGui window or item is hovered
        if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) || ImGui::IsAnyItemHovered())
        {
            continue;
        }

        switch (event.type)
        {

            case SDL_MOUSEWHEEL: adjustScale(event, scale); break;

            case SDL_MOUSEBUTTONDOWN:
                handleMouseButtonDown(event, middleMouseButtonPressed, mouseStartPanX,
                                      mouseStartPanY, scale);
                break;

            case SDL_MOUSEBUTTONUP:
                handleMouseButtonUp(event, middleMouseButtonPressed, offsetX, offsetY, offsetEndX,
                                    offsetEndY);
                break;

            default: break;
        }
    }
}

void App::adjustScale(const SDL_Event &event, float &scale)
{
    if (event.wheel.y > 0) { scale *= 1.05f; }
    else if (event.wheel.y < 0) { scale *= 0.95f; }
}

void App::handleMouseButtonDown(const SDL_Event &event,
                                bool &middleMouseButtonPressed,
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

void App::handleMouseButtonUp(const SDL_Event &event,
                              bool &middleMouseButtonPressed,
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

void App::handleKeyDown(const SDL_Event &event,
                        float &scale,
                        float &offsetX,
                        float &offsetY,
                        float &offsetEndX,
                        float &offsetEndY)
{
    switch (event.key.keysym.sym)
    {
        case SDLK_m: offsetX = offsetY = offsetEndX = offsetEndY = 0.0f; break;

        case SDLK_z: scale = 1.0f; break;

        default: break;
    }
}

void App::handleMouseMotion(bool middleMouseButtonPressed,
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

void App::clampScale(float &scale)
{
    if (scale < 1.05f && scale > 0.95f) { scale = 1.0f; }
    else if (scale >= 5.0f) { scale = 5.0f; }
    else if (scale <= 0.5f) { scale = 0.5f; }
}

void App::finalizeFrame()
{
    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) { SDL_Delay(frameDelay - frameTime); }
}

int App::RunEngine()
{
    if (!initialize())
    {
        std::cerr << "Failed to initialize!" << std::endl;
        return 1;
    }

    // I understand that I could've set them as private variables in my class
    // but IDK for some reason they don't work, so I set them here as local
    // variables, it's also less overhead.
    float offsetX                 = 0.0f;
    float offsetY                 = 0.0f;
    float offsetEndX              = 0.0f;
    float offsetEndY              = 0.0f;
    float mouseStartPanX          = 0.0f;
    float mouseStartPanY          = 0.0f;
    float scale                   = 1.0f;
    bool middleMouseButtonPressed = false;
    SDL_Event event;

    while (!m_quit)
    {
        frameStart = SDL_GetTicks();
        calcDeltatime();

        processEvents(event, scale, middleMouseButtonPressed, mouseStartPanX, mouseStartPanY,
                      offsetX, offsetY, offsetEndX, offsetEndY, m_quit);
        handleMouseMotion(middleMouseButtonPressed, scale, mouseStartPanX, mouseStartPanY, offsetX,
                          offsetY, offsetEndX, offsetEndY);
        clampScale(scale);

        update(scale, offsetX, offsetY);
        render();
    }

    finalizeFrame();

    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) { SDL_Delay(frameDelay - frameTime); }

    close();

    if (m_window != nullptr) { std::cout << "Window failed to close"; }
    if (m_renderer != nullptr) { std::cout << "Renderer failed to close"; }

    return 0;
}
