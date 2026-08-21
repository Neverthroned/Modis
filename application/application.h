#ifndef APPLICATION_H
#define APPLICATION_H

struct SDL_Window;
struct SDL_GLContextState;

class Application
{
    public:
    Application();
    ~Application();

    SDL_Window* GetWindow();

    bool Init();
    void Run();

    private:
    SDL_Window* window;
    
    // GLContext Variables
    SDL_GLContextState* context;
};

#endif