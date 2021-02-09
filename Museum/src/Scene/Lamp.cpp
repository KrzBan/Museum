#include "Lamp.h"

#include "Model.h"

Lamp::Lamp() {
	bodyModel = std::make_shared<Model>("res/models/museum/lamp/lamp_body.obj");
	bodyModel->InsertTexture("res/textures/misc/black.jpg", TEX_TYPE::TEX_DIFFUSE);
	bodyModel->transform.SetScale(0.01f);
	bodyModel->transform.PutOnGround();
	bodyModel->transform.Translate(0.0f, 4 - bodyModel->transform.size.y / 2, 0.0f);
	bodyModel->castShadows = false;
	bodyModel->ReveiceShadows(false);

	lightModel = std::make_shared<Model>("res/models/museum/lamp/lamp_light.obj");
	lightModel->InsertTexture("res/models/museum/lamp/lamp_light_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	lightModel->transform.SetParent(&bodyModel->transform);
	lightModel->castShadows = false;
	lightModel->ReveiceShadows(false);
}