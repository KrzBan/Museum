#pragma once

#include "PerspectiveCamera.h"
#include "Object.h"
#include "Input.h"

class CameraController: public Object {
public:
	CameraController(float aspectRatio)
		: camera(aspectRatio) {

	}

	PerspectiveCamera camera;

	void OnUpdate(float deltaTime) override {

        float maxDistance = 9.0f;

        float speed = 5.0f * deltaTime;
        glm::vec3 deltaPos = glm::vec3{ 0.0f };
        glm::vec3 fixedForward = camera.forward;

        fixedForward.y = 0;
        if (Input::GetKey('w')) 
            deltaPos += fixedForward;
        if (Input::GetKey('s')) 
            deltaPos += -fixedForward;
        if (Input::GetKey('a')) 
            deltaPos += -camera.right;
        if (Input::GetKey('d')) 
            deltaPos += camera.right;
         
        deltaPos = speed * glm::normalize(deltaPos);
        if (glm::any(glm::isnan(deltaPos)) == false)
            camera.position += deltaPos;
        
        float dist = std::sqrtf(camera.position.x * camera.position.x + camera.position.z * camera.position.z);
        if (dist > maxDistance) {
            camera.position *= maxDistance / dist;
        }
        camera.position.y = 1.8f;

        float mouseSensitivity = 10.0f * deltaTime;

        camera.ProcessMouseMovement(static_cast<float>(Input::GetMouseDeltaX()) * mouseSensitivity, static_cast<float>(Input::GetMouseDeltaY()) * mouseSensitivity);
	}

};
