#ifndef RENDER_H
#define RENDER_H

#include "shader.h"
#include "camera.h"

class Render
{
public:
    Render();
    ~Render();

    bool Init();
    void RenderScreen();

private:
    unsigned int texture;
    unsigned int VAO, VBO;
    unsigned int EBO;
    unsigned char *data;
    Camera m_Camera;
    Shader shader;
};

#endif