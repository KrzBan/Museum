#include "SolarSystem.h"

#include "Model.h"

SolarSystem::SolarSystem() {
	sunModel = std::make_shared<Model>("res/models/prim/sphere.obj");
	sunModel->InsertTexture("res/models/solar/Sun_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	sunModel->transform.SetScale(0.002f);
	sunModel->transform.PutOnGround();
	sunModel->transform.Translate(0.0f, -1.4f, 0.0f);
	sunModel->ReveiceShadows(false);

	mercuryTransform = std::make_shared<Transform>(false);
	mercuryTransform->SetParent(&sunModel->transform);
	mercuryModel = std::make_shared<Model>("res/models/prim/sphere.obj", false);
	mercuryModel->InsertTexture("res/models/solar/Mercury_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	mercuryModel->transform.Translate(1.2*distance, 0.0f, 0.0f);
	mercuryModel->transform.Rotate(-70.0f, 0.0f, 0.0f);
	mercuryModel->transform.SetParent(&*mercuryTransform);
	mercuryModel->transform.SetScale(planetScale* 0.09);

	venusTransform = std::make_shared<Transform>(false);
	venusTransform->SetParent(&sunModel->transform);
	venusModel = std::make_shared<Model>("res/models/prim/sphere.obj", false);
	venusModel->InsertTexture("res/models/solar/Venus_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	venusModel->transform.Translate(2*distance, 0.0f, 0.0f);
	venusModel->transform.Rotate(-70.0f, 0.0f, 0.0f);
	venusModel->transform.SetParent(&*venusTransform);
	venusModel->transform.SetScale(planetScale * 0.1);

	earthTransform = std::make_shared<Transform>(false);
	earthTransform->SetParent(&sunModel->transform);
	earthModel = std::make_shared<Model>("res/models/prim/sphere.obj", false);
	earthModel->InsertTexture("res/models/solar/Earth_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	earthModel->transform.Translate(3*distance, 0.0f, 0.0f);
	earthModel->transform.Rotate(-70.0f, 0.0f, 0.0f);
	earthModel->transform.SetParent(&*earthTransform);
	earthModel->transform.SetScale(planetScale * 0.2);

	marsTransform = std::make_shared<Transform>(false);
	marsTransform->SetParent(&sunModel->transform);
	marsModel = std::make_shared<Model>("res/models/prim/sphere.obj", false);
	marsModel->InsertTexture("res/models/solar/Mars_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	marsModel->transform.Translate(4*distance, 0.0f, 0.0f);
	marsModel->transform.Rotate(-70.0f, 0.0f, 0.0f);
	marsModel->transform.SetParent(&*marsTransform);
	marsModel->transform.SetScale(planetScale * 0.15);

	jupiterTransform = std::make_shared<Transform>(false);
	jupiterTransform->Rotate(0.0f, 240.0f, 0.0f);
	jupiterTransform->SetParent(&sunModel->transform);
	jupiterModel = std::make_shared<Model>("res/models/solar/Jupiter.fbx");
	jupiterModel->InsertTexture("res/models/solar/Jupiter_diffuse.png", TEX_TYPE::TEX_DIFFUSE);
	jupiterModel->InsertTexture("res/models/solar/Jupiter_specular.png", TEX_TYPE::TEX_SPECULAR);
	jupiterModel->InsertTexture("res/models/solar/Jupiter_normal.png", TEX_TYPE::TEX_NORMAL);
	jupiterModel->transform.Translate(5*distance, 0.0f, 0.0f);
	jupiterModel->transform.Rotate(70.0f, 0.0f, 0.0f);
	jupiterModel->transform.SetParent(&*jupiterTransform);
	jupiterModel->transform.SetScale(planetScale * 0.4 * 5);

	saturnTransform = std::make_shared<Transform>(false);
	saturnTransform->Rotate(0.0f, 60.0f, 0.0f);
	saturnTransform->SetParent(&sunModel->transform);
	saturnModel = std::make_shared<Model>("res/models/solar/Jupiter.fbx");
	saturnModel->InsertTexture("res/models/solar/Saturn_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	saturnModel->InsertTexture("res/models/solar/Jupiter_specular.png", TEX_TYPE::TEX_SPECULAR);
	saturnModel->InsertTexture("res/models/solar/Jupiter_normal.png", TEX_TYPE::TEX_NORMAL);
	saturnModel->transform.Translate(6*distance, 0.0f, 0.0f);
	saturnModel->transform.Rotate(70.0f, 0.0f, 0.0f);
	saturnModel->transform.SetParent(&*saturnTransform);
	saturnModel->transform.SetScale(planetScale * 0.35 * 5);

	uranusTransform = std::make_shared<Transform>(false);
	uranusTransform->Rotate(0.0f, 150.0f, 0.0f);
	uranusTransform->SetParent(&sunModel->transform);
	uranusModel = std::make_shared<Model>("res/models/prim/sphere.obj", false);
	uranusModel->InsertTexture("res/models/solar/Uranus_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	uranusModel->transform.Translate(7*distance, 0.0f, 0.0f);
	uranusModel->transform.Rotate(-70.0f, 0.0f, 0.0f);
	uranusModel->transform.SetParent(&*uranusTransform);
	uranusModel->transform.SetScale(planetScale * 0.2);

	neptuneTransform = std::make_shared<Transform>(false);
	neptuneTransform->SetParent(&sunModel->transform);
	neptuneModel = std::make_shared<Model>("res/models/prim/sphere.obj", false);
	neptuneModel->InsertTexture("res/models/solar/Neptune_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	neptuneModel->transform.Translate(8*distance, 0.0f, 0.0f);
	neptuneModel->transform.Rotate(-70.0f, 0.0f, 0.0f);
	neptuneModel->transform.SetParent(&*neptuneTransform);
	neptuneModel->transform.SetScale(planetScale * 0.1);
}

void SolarSystem::OnUpdate(float deltaTime) {
	deltaTime *= 5;

	mercuryTransform->Rotate(0.0f, deltaTime * 4.0f, 0.0f);

	venusTransform->Rotate(0.0f, deltaTime * 1.6f, 0.0f);

	earthTransform->Rotate(0.0f, deltaTime * 1.0f, 0.0f);

	marsTransform->Rotate(0.0f, deltaTime * 0.52f, 0.0f);
	
	jupiterTransform->Rotate(0.0f, deltaTime * 0.083f, 0.0f);

	saturnTransform->Rotate(0.0f, deltaTime * 0.033f, 0.0f);

	uranusTransform->Rotate(0.0f, deltaTime * 0.011f, 0.0f);

	neptuneTransform->Rotate(0.0f, deltaTime * 0.006f, 0.0f);
}