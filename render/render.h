#ifndef RENDER_H
#define RENDER_H

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
    unsigned int shaderProgram;
    unsigned char *data;
};

#endif