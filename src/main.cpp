#include <iostream>
#include <SDL3/SDL.h>

int main()
{
    // Window Variables
    SDL_Window *window;

    // Event Variables
    bool done = false;

    // GLContext Variables
    SDL_GLContext context;
    


    // SDL Initialization
    bool init = SDL_Init(SDL_INIT_VIDEO);

    if (init == false) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize: %s\n", SDL_GetError());
        return 1;
    }

    bool majorVersion = SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    if (majorVersion == false) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Major version error: %s\n", SDL_GetError());
        return 1;
    }
    bool minorVersion = SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    if (minorVersion == false) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Minor version error: %s\n", SDL_GetError());
        return 1;
    }
    bool profile = SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    if (profile == false) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "GL profile error: %s\n", SDL_GetError());
        return 1;
    }

    std::cout << "SDL initialized successfully!" << std::endl;

    // Window Creation
    window = SDL_CreateWindow(
        "Modis",
        800,
        600,
        SDL_WINDOW_OPENGL);

    if (window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    // OpenGL Context Creation
    context = SDL_GL_CreateContext(window);

    if (context == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create context: %s\n", SDL_GetError());
        return 1;
    }

    // Event Handling
    while (!done)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                done = true;
            }
        }

        // Do game logic, frames etc.
    }

    // Destroy OpenGL Context
    SDL_GL_DestroyContext(context);

    // Close Window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}
