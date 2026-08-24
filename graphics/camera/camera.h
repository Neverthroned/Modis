#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
    public:
    Camera(float left, float right, float bottom, float top);
    ~Camera();
    bool Init();

    void SetPosition(const glm::vec3& position) {m_Position = position;}

    private:
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;

    glm::vec3 m_Position;

};

#endif