#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "render.h"
#include "utilities.h"
#include "shader.h"
#include <glad/gl.h>

Render::Render()
{
    data = nullptr;
    VAO = 0;
    VBO = 0;
    EBO = 0;
    texture = 0;
}

Render::~Render()
{
    // Delete VBO and EBO
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // Delete VAO
    glDeleteVertexArrays(1, &VAO);

    // Delete Textures
    glDeleteTextures(1, &texture);

    // Free image data
    stbi_image_free(data);
}

bool Render::Init()
{
    // Construct Utilities
    Utilities util;

    // Create array for vertex coordinate positions
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Bottom-left corner
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // Bottom-right corner
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // Top-right corner
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f   // Top-left corner
    };

    // Assign indices order for quad
    unsigned int indices[] = {
        0, 1, 2, 0, 2, 3};

    // Generate vertex array object names
    glGenVertexArrays(1, &VAO);
    // Generate buffer object names
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Image parameters
    int width, height, channels;

    // Load texture
    data = stbi_load("textures/myTexture.png", &width, &height, &channels, 4);

    if (data == nullptr)
    {
        // Retrieve failure
        std::cout << "Failed to load texture: " << stbi_failure_reason() << std::endl;
        return false;
    }

    std::cout << "Loaded image: " << width << "x" << height << " with " << channels << " channels.\n";

    // Generate and bind textures
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Bind the vertex array object
    glBindVertexArray(VAO);

    // For the GL_ARRAY_BUFFER binding point, make VBO the currently bound buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Texture parameters (for pixelated png quality and edge clamping)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // More image parameters and generate mipmap
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

    if (!shader.Init())
        return false;

    return true;
}

void Render::RenderScreen()
{
    // Full window color
    glClearColor(0.4, 0.3, 0.95, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.Use();
    shader.SetInt("myTexture", 0);

    // Bind texture
    glBindTexture(GL_TEXTURE_2D, texture);

    // Bind vertex array in loop and draw quad
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}