#include <iostream>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "render.h"
#include "utilities.h"
#include "shader.h"
#include "camera.h"
#include <glad/gl.h>

#include "terrain.h"
#include "tileRegistry.h"

Render::Render()
    : m_Camera(-1.0f, 32.0f, -1.0f, 32.0f)
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

void Render::BuildTerrainMesh(const Terrain &terrain)
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (int y = 0; y < 32; y++)
    {
        for (int x = 0; x < 32; x++)
        {
            // Get tiles from terrain
            TileType type = terrain.GetTile(x, y);

            // assign variables for position
            float left = static_cast<float>(x);
            float right = left + 1.0f;
            float bottom = static_cast<float>(y);
            float top = bottom + 1.0f;

            // Automate Insertion of vertices
            // Bottom-left
            vertices.insert(vertices.end(), {left, bottom, 0.0f, 0.0f, 0.0f});

            // Bottom-right
            vertices.insert(vertices.end(), {right, bottom, 0.0f, 1.0f, 0.0f});

            // Top-right
            vertices.insert(vertices.end(), {right, top, 0.0f, 1.0f, 1.0f});

            // Top-left
            vertices.insert(vertices.end(), {left, top, 0.0f, 0.0f, 1.0f});

            unsigned int vertexOffset = (y * 32 + x) * 4;

            indices.insert(indices.end(), {vertexOffset,
                                           vertexOffset + 1,
                                           vertexOffset + 2,

                                           vertexOffset,
                                           vertexOffset + 2,
                                           vertexOffset + 3});
        }
    }

    // Bind buffers and buffer data
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
        GL_STATIC_DRAW);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW);

    indexCount = static_cast<unsigned int>(indices.size());
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

    shader.UploadUniformMat4("u_ViewProjection", m_Camera.GetViewProjectionMatrix());

    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}