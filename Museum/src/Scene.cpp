#include "Scene.h"

#include "Components/Transform.h"

#include <iostream>

struct SceneData {

	SceneData() : transform{ false } {}

	Transform transform;
};

std::unique_ptr<SceneData> sceneData;

void Scene::Init() {
	sceneData = std::make_unique<SceneData>();
}

Transform& Scene::GetTransform() {
	return sceneData->transform;
}