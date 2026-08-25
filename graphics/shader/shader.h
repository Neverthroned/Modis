#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader
{
    public:
    Shader();
    ~Shader();

    bool Init();
    
    void Use();
    void SetInt(const std::string& name, int value);

    private:
    unsigned int shaderProgram;

};

#endif