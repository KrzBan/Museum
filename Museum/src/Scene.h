#pragma once

#include "Scene/Building.h"
#include "Scene/SolarSystem.h"

class Transform;

class Scene {
public:
	static void Init();

	static Transform& GetTransform();
};