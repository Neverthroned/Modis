#include <iostream>
#include "render.h"
#include <glad/gl.h>

Render::Render()
{
}

Render::~Render()
{
    // Delete Program
    glDeleteProgram(shaderProgram);

    // Delete VBO
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // Delete VAO
    glDeleteVertexArrays(1, &VAO);
}

bool Render::Init()
{
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
}
