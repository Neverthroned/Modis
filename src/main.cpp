#include <iostream>

#include <glad/gl.h>
#include <SDL3/SDL.h>

const GLuint WIDTH = 800, HEIGHT = 600;



GLuint VAO, VBO;
GLuint shaderProgram;

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
        WIDTH,
        HEIGHT,
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

    // Load GLAD
    int gLVersion = gladLoaderLoadGL();
    
    if (gLVersion == 0) {
        std::cout << "GLAD Failed" << std::endl;
        return 1;
    }

    std::cout << "GL " << GLAD_VERSION_MAJOR(gLVersion) << "." << GLAD_VERSION_MINOR(gLVersion) << std::endl;

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl <<
    "Renderer: " << glGetString(GL_RENDERER) << std::endl <<
    "Version: " << glGetString(GL_VERSION) << std::endl <<
    "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // Match Framerate
    SDL_GL_SetSwapInterval(1);

    // Create array for vertex coordinate positions
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // Bottom-left corner
        0.5f, -0.5f, 0.0f, // Bottom-right corner
        0.0f, 0.5f, 0.0f // Top corner
    };

    // Generate vertex array object names
    glGenVertexArrays(1, &VAO);
    // Generate buffer object names
    glGenBuffers(1, &VBO);

    // Bind the vertex array object
    glBindVertexArray(VAO);

    // For the GL_ARRAY_BUFFER binding point, make VBO the currently bound buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Create and initialize buffer object data store, pass vertices to array buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Create Shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (vertexShader == 0) {
        std::cout << "Vertex shader failure" << std::endl;
    }
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (fragmentShader == 0) {
        std::cout << "Fragment shader failure" << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

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

        
        

        // glClearColor(0.4, 0.3, 0.95, 1);
        // glClear(GL_COLOR_BUFFER_BIT);

        // Draw the triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap Buffer
        SDL_GL_SwapWindow(window);
    }

    // Unload GLAD
    gladLoaderUnloadGL();

    // Destroy OpenGL Context
    SDL_GL_DestroyContext(context);

    // Close Window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}
