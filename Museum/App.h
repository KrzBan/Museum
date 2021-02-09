#pragma once

#include "src/Components/CameraController.h"
#include "src/Components/Light.h"
#include "src/Components/ShadowMap.h"
#include "src/Components/HDR.h"
#include "src/Buffer.h"
#include "src/VertexArray.h"
#include "src/Texture.h"
#include "src/Shader.h"
#include "src/Model.h"

class App {
public:
	App(int screenWidth,int screenHeight);

	void Draw();
	void Idle();
	void Resize(int width, int height);

	void Render();
	void RenderShadows();
	void AddHDR();

private:
	int m_ScreenWidth = 640;
	int m_ScreenHeight = 480;

	//for shadows
	bool m_DrawShadows = true;
	bool m_GenerateShadows = true;
	bool m_SoftShadows = true;
	bool m_UseLights = true;
	bool m_UseHDR = true;
	float m_Exposure = 1.0f;

	const float nearPlane = 0.1f;
	const float farPlane = 100.0f;

	std::unique_ptr<CameraController> mainCamera;
	std::vector<PointLight> pointLights;

	std::shared_ptr<HDR> hdr;
	std::shared_ptr<ShadowMap> shadowMap;

	std::shared_ptr<Shader> shaderModel;
	std::shared_ptr<Shader> shaderShadow;
	std::shared_ptr<Shader> shaderHDR;

	//Scene
	Building building;
	SolarSystem solarSystem;
};