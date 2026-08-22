#include <iostream>
#include <fstream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "application.h"
#include <glad/gl.h>
#include <SDL3/SDL.h>

GLuint texture;
GLuint VAO, VBO;
GLuint EBO;
GLuint shaderProgram;

// File-opening function
std::string openFile(std::string path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cout << path << "isn't open" << std::endl;
        return "";
    }

    // Write complete string to buffer
    std::stringstream buffer;
    buffer << file.rdbuf();

    // Write buffer to contents string
    std::string contents = buffer.str();

    // File cleanup and return
    file.close();
    return contents;
}

int main()
{
    Application app;

    bool success = app.Init();
    if (success == false)
    {
        return 1;
    }

        // Create array for vertex coordinate positions
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Bottom-left corner
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // Bottom-right corner
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // Top-right corner
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f   // Top-left corner
    };

    unsigned int indices[] = {
        0, 1, 2, 0, 2, 3};

    // Generate vertex array object names
    glGenVertexArrays(1, &VAO);
    // Generate buffer object names
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    int width, height, channels;

    unsigned char *data = stbi_load("textures/myTexture.png", &width, &height, &channels, 4);

    if (data == nullptr)
    {
        // Retrieve failure
        std::cout << "Failed to load texture: " << stbi_failure_reason() << std::endl;
        return 1;
    }

    std::cout << "Loaded image: " << width << "x" << height << " with " << channels << " channels.\n";

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Bind the vertex array object
    glBindVertexArray(VAO);

    // For the GL_ARRAY_BUFFER binding point, make VBO the currently bound buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Create and initialize buffer object data store, pass vertices to array buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // UV attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Create Shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (vertexShader == 0)
    {
        std::cout << "Vertex shader failure" << std::endl;
        return 1;
    }
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (fragmentShader == 0)
    {
        std::cout << "Fragment shader failure" << std::endl;
        return 1;
    }

    std::string vertexString = openFile("shaders/vertex.glsl");
    std::string fragmentString = openFile("shaders/fragment.glsl");

    const GLchar *vertexSource = vertexString.c_str();
    const GLchar *fragmentSource = fragmentString.c_str();

    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

    // Compile Shaders
    GLint gSuccess;
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &gSuccess);
    if (!gSuccess)
    {
        GLchar error[1024];
        glGetShaderInfoLog(vertexShader, 1024, NULL, error);
        std::cout << "Vertex shader failed to compile: " << error << std::endl;
        return 1;
    }

    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &gSuccess);
    if (!gSuccess)
    {
        GLchar error[1024];
        glGetShaderInfoLog(fragmentShader, 1024, NULL, error);
        std::cout << "Fragment shader failed to compile: " << error << std::endl;
        return 1;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &gSuccess);
    if (!gSuccess)
    {
        GLchar error[1024];
        glGetProgramInfoLog(shaderProgram, 1024, NULL, error);
        std::cout << "Program failed to link: " << error << std::endl;
        return 1;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Event Handling
    while (app.Run())
    {
        // Do game logic, frames etc.

        glClearColor(0.4, 0.3, 0.95, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the triangle
        glUseProgram(shaderProgram);
        int location = glGetUniformLocation(shaderProgram, "myTexture");
        glUniform1i(location, 0);

        glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap Buffer
        app.Present();
    }

    // Delete Program
    glDeleteProgram(shaderProgram);

    // Delete VBO
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // Delete VAO
    glDeleteVertexArrays(1, &VAO);

    // Delete Textures
    glDeleteTextures(1, &texture);

    stbi_image_free(data);

    return 0;
}
