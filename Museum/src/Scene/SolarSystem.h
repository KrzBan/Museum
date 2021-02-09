#pragma once

#include <iostream>

#include "Object.h"

class Model;
class Transform;

class SolarSystem : public Object {
public:
	SolarSystem();

	float distance = 180.0f;
	float planetScale = 4.0f;

	std::shared_ptr<Model> sunModel;

	std::shared_ptr<Transform> jupiterTransform;
	std::shared_ptr<Model> jupiterModel;

	std::shared_ptr<Transform> earthTransform;
	std::shared_ptr<Model> earthModel;

	std::shared_ptr<Transform> neptuneTransform;
	std::shared_ptr<Model> neptuneModel;

	std::shared_ptr<Transform> uranusTransform;
	std::shared_ptr<Model> uranusModel;

	std::shared_ptr<Transform> marsTransform;
	std::shared_ptr<Model> marsModel;

	std::shared_ptr<Transform> venusTransform;
	std::shared_ptr<Model> venusModel;

	std::shared_ptr<Transform> mercuryTransform;
	std::shared_ptr<Model> mercuryModel;

	std::shared_ptr<Transform> saturnTransform;
	std::shared_ptr<Model> saturnModel;

	void OnUpdate(float deltaTime) override;
};