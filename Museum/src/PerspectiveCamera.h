#pragma once

#include "Utility.h"

class PerspectiveCamera
{
public:
    // camera Attributes
    glm::vec3 position  = { 0.0f, 0.0f, 0.0f };
    glm::vec3 forward;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp   = { 0.0f, 1.0f, 0.0f };

    // euler Angles
    float yaw = 90.0f; //these dont work
    float pitch = 0.0f;

private:
    glm::mat4 m_ProjMatrix;
    glm::mat4 m_ViewProjMatrix;

    float m_Fov = glm::radians(70.0f);
    float m_NearPlane = 0.1f;
    float m_FarPlane = 100.0f;

public:
    PerspectiveCamera(float aspectRatio);

    void UpdateAspectRatio(float aspectRatio);

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    const glm::mat4& GetProjMatrix()const {
        return m_ProjMatrix;
    }
    const glm::mat4& GetViewProjMatrix()const {
        return m_ViewProjMatrix;
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

private:
    void UpdateCameraVectors();
};

