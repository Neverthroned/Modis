#ifndef APPLICATION_H
#define APPLICATION_H

#include "render.h"

struct SDL_Window;
struct SDL_GLContextState;

class Application
{
public:
    Application();
    ~Application();

    bool Init();
    void Run();
    bool ProcessEvents();
    void Present();

private:
    SDL_Window *window;

    // GLContext Variables
    SDL_GLContextState *context;

    Render ren;
};

#endif