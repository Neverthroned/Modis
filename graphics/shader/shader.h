#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>

class Shader
{
    public:
    Shader();
    ~Shader();

    bool Init();
    
    void Use();
    void SetInt(const std::string& name, int value);

    void UploadUniformMat4(const std::string& name, const glm::mat4 &matrix);

    private:
    unsigned int shaderProgram;

};

#endif