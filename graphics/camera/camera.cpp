#include <iostream>
#include "camera.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float left, float right, float bottom, float top)
    : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
{
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

Camera::~Camera()
{
}

void Camera::RecalculateViewMatrix()
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0, 0, 1));

    m_ViewMatrix = glm::inverse(transform);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

bool Camera::Init()
{
}

void Camera::SetPosition(const glm::vec3 &position)
{
}