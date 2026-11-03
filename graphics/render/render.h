#ifndef RENDER_H
#define RENDER_H

#include "shader.h"
#include "camera.h"

class Terrain;

class Render
{
public:
    Render();
    ~Render();

    bool Init();
    void BuildTerrainMesh(const Terrain& terrain);
    void RenderScreen();

private:
    unsigned int texture;
    unsigned int VAO, VBO;
    unsigned int EBO;
    unsigned char *data;
    unsigned int indexCount = 0;
    Camera m_Camera;
    Shader shader;
};

#endif