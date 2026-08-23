#ifndef SHADER_H
#define SHADER_H

class Shader
{
    public:
    Shader();
    ~Shader();

    bool Init();

    private:
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;

};

#endif