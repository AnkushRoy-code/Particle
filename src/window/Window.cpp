#include "window/Window.h"

void WindowManager::initialise(SDL_Window *&window, SDL_GLContext glContext)
{
    m_SDLManager.initialise(window, glContext);
    m_openglManager.initialise(window, glContext);
}

void WindowManager::close(SDL_Window *&window, SDL_GLContext glContext)
{
    m_openglManager.close(glContext);
    m_SDLManager.close(window);
}
