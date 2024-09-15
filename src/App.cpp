#include "App.h"

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
    m_windowManager.initialise(m_window, m_glContext);

    int h, w;
    SDL_GetWindowSize(m_window, &w, &h);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        SDL_GL_DeleteContext(m_glContext);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    m_UI.initialise(m_window, m_glContext, w, h);
    // IDK how to check if imgui was successfully initialised.
    return true;
}

void App::update(float Scale, float offSetX, float offSetY)
{
    m_UI.setup();
    m_UI.update(m_window, m_glContext, deltaTime, Scale, offSetX, offSetY);

    int h, w;
    SDL_GetWindowSize(m_window, &w, &h);

    m_UI.setSize(w, h);
}

void App::render() {}

void App::close()
{
    m_UI.close();
    m_windowManager.close(m_window, m_glContext);
}

void App::finalizeFrame()
{
    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) { SDL_Delay(frameDelay - frameTime); }
}

int App::RunEngine(App Engine)
{
    if (!Engine.initialize())
    {
        std::cerr << "Failed to initialize!" << std::endl;
        return 1;
    }

    float offsetX                 = 0.0f;
    float offsetY                 = 0.0f;
    float offsetEndX              = 0.0f;
    float offsetEndY              = 0.0f;
    float mouseStartPanX          = 0.0f;
    float mouseStartPanY          = 0.0f;
    float scale                   = 1.0f;
    bool middleMouseButtonPressed = false;

    while (!Engine.m_quit)
    {
        frameStart = SDL_GetTicks();
        calcDeltatime();

        m_inputHandler.processEvents(m_window, scale, middleMouseButtonPressed, mouseStartPanX,
                                     mouseStartPanY, offsetX, offsetY, offsetEndX, offsetEndY,
                                     Engine.m_quit);

        m_inputHandler.handleMouseMotion(middleMouseButtonPressed, scale, mouseStartPanX,
                                         mouseStartPanY, offsetX, offsetY, offsetEndX, offsetEndY);

        clampScale(scale);

        Engine.update(scale, offsetX, offsetY);
        Engine.render();
    }

    finalizeFrame();

    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) { SDL_Delay(frameDelay - frameTime); }

    Engine.close();

    return 0;
}

void App::clampScale(float &scale)
{
    if (scale < 1.05f && scale > 0.95f) { scale = 1.0f; }
    else if (scale >= 5.0f) { scale = 5.0f; }
    else if (scale <= 0.5f) { scale = 0.5f; }
}
