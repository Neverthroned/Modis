#ifndef RENDER_H
#define RENDER_H

#include "shader.h"

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
    Shader shader;
};

#endif