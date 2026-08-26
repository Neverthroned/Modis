#include <iostream>
#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "utilities.h"

Shader::Shader()
{
    shaderProgram = 0;
}

Shader::~Shader()
{
    // Delete Program
    glDeleteProgram(shaderProgram);
}

bool Shader::Init()
{
    Utilities util;

    // Create Shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (vertexShader == 0)
    {
        std::cout << "Vertex shader failure" << std::endl;
        return false;
    }
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (fragmentShader == 0)
    {
        std::cout << "Fragment shader failure" << std::endl;
        return false;
    }

    // Open shader files using Utilities
    std::string vertexString = util.openFile("shaders/vertex.glsl");
    std::string fragmentString = util.openFile("shaders/fragment.glsl");

    // Turn string into readable data
    const GLchar *vertexSource = vertexString.c_str();
    const GLchar *fragmentSource = fragmentString.c_str();

    // Grab shader sources
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

    // Compile Shaders
    int success;
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar error[1024];
        glGetShaderInfoLog(vertexShader, 1024, NULL, error);
        std::cout << "Vertex shader failed to compile: " << error << std::endl;
        return false;
    }

    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar error[1024];
        glGetShaderInfoLog(fragmentShader, 1024, NULL, error);
        std::cout << "Fragment shader failed to compile: " << error << std::endl;
        return false;
    }

    // Create shaderProgram and attach, link and debug shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar error[1024];
        glGetProgramInfoLog(shaderProgram, 1024, NULL, error);
        std::cout << "Program failed to link: " << error << std::endl;
        return false;
    }

    // Cleanup shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

void Shader::Use()
{
    glUseProgram(shaderProgram);
}

void Shader::SetInt(const std::string& name, int value)
{
    // Set location and texture
    int location = glGetUniformLocation(shaderProgram, name.c_str());
    glUniform1i(location, value);
}

void Shader::UploadUniformMat4(const std::string &name, const glm::mat4 &matrix)
{
    // Upload u_ViewProjection to shader GLSL
    int location = glGetUniformLocation(shaderProgram, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
