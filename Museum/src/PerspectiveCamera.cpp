#include "PerspectiveCamera.h"

#include <iostream>

PerspectiveCamera::PerspectiveCamera(float aspectRatio) : forward(glm::vec3(0.0f, 0.0f, -1.0f)),
m_ProjMatrix(glm::perspective(m_Fov, aspectRatio, m_NearPlane, m_FarPlane))
{
    UpdateCameraVectors();
}

void PerspectiveCamera::UpdateAspectRatio(float aspectRatio) {
    m_ProjMatrix = glm::perspective(m_Fov, aspectRatio, m_NearPlane, m_FarPlane);
    UpdateCameraVectors();
}

void PerspectiveCamera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }
    UpdateCameraVectors();
}

void PerspectiveCamera::UpdateCameraVectors(){
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward = glm::normalize(front);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(forward, worldUp));
    up = glm::normalize(glm::cross(right, forward));

    auto viewMatrix = glm::lookAt(position, position + forward, up);
    m_ViewProjMatrix = m_ProjMatrix * viewMatrix;
}