#include <iostream>
#include "application.h"
#include "render.h"
#include <SDL3/SDL.h>
#include <glad/gl.h>

const unsigned int WIDTH = 800, HEIGHT = 600;

Application::Application()
{
    window = nullptr;
    context = nullptr;
}

Application::~Application()
{
    // Unload GLAD
    gladLoaderUnloadGL();

    // Destroy OpenGL Context
    SDL_GL_DestroyContext(context);

    // Close Window
    SDL_DestroyWindow(window);

    // Close SDL
    SDL_Quit();
}

bool Application::Init()
{
    // Initialize SDL
    bool init = SDL_Init(SDL_INIT_VIDEO);

    if (init == false)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize: %s\n", SDL_GetError());
        return false;
    }

    // Glad version check
    bool majorVersion = SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    if (majorVersion == false)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Major version error: %s\n", SDL_GetError());
        return false;
    }
    bool minorVersion = SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    if (minorVersion == false)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Minor version error: %s\n", SDL_GetError());
        return false;
    }
    bool profile = SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    if (profile == false)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "GL profile error: %s\n", SDL_GetError());
        return false;
    }

    std::cout << "SDL initialized successfully!" << std::endl;

    // Window Creation
    window = SDL_CreateWindow(
        "Modis",
        WIDTH,
        HEIGHT,
        SDL_WINDOW_OPENGL);

    if (window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return false;
    }

    // OpenGL Context Creation
    context = SDL_GL_CreateContext(window);

    if (context == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create context: %s\n", SDL_GetError());
        return false;
    }

    // Load GLAD
    int gLVersion = gladLoaderLoadGL();

    if (gLVersion == 0)
    {
        std::cout << "GLAD Failed" << std::endl;
        return false;
    }

    std::cout << "GL " << GLAD_VERSION_MAJOR(gLVersion) << "." << GLAD_VERSION_MINOR(gLVersion) << std::endl;

    // Debug for GLAD
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl
              << "Renderer: " << glGetString(GL_RENDERER) << std::endl
              << "Version: " << glGetString(GL_VERSION) << std::endl
              << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // Match Framerate
    SDL_GL_SetSwapInterval(1);

    if (!ren.Init())
        return false;

    return true;
}

void Application::Run()
{
    bool running = true;

    while (running)
    {
        // Run processes
        running = ProcessEvents();
        ren.RenderScreen();
        Present();
    }
}

void Application::Present()
{
    SDL_GL_SwapWindow(window);
}

bool Application::ProcessEvents()
{
    // Event Handling
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            return false;
        }
    }
    return true;
}