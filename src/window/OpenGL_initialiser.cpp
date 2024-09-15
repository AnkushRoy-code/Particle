#include "window/OpenGL_initialiser.h"

void openGLManager::initialise(SDL_Window *window, SDL_GLContext glContext)
{
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    glViewport(0, 0, w, h);
    m_shader.initialise("res/shaders/shader.vert", "res/shaders/shader.frag");
}

void openGLManager::close(SDL_GLContext glContext)
{
    SDL_GL_DeleteContext(glContext);
    m_shader.close();
}
