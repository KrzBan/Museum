#pragma once

#include <vector>
#include <memory>

#include "Utility.h"
#include "Shader.h"

class PointLight {
	static uint32_t s_LightCount;
	static uint32_t s_ShadowCasters;
	
public:
	glm::vec3 position;
	glm::vec3 diffuse;
	glm::vec3 ambient;
	glm::vec3 specular;
	bool castsShadows;

	PointLight() :
		position{ 1.0f }, diffuse{ 1.0f }, ambient{ 1.0f }, specular{ 1.0f }, castsShadows{ false }{
		++s_LightCount;
	}

	PointLight(bool castsShadows, const glm::vec3& pos, const glm::vec3& diff, float ambiStrength = 3.0f) :
		castsShadows{ castsShadows }, position{ pos }, diffuse{ diff }, ambient{ diff*ambiStrength }, specular{ diff }{
		if (castsShadows) ++s_ShadowCasters;
		++s_LightCount;
	}

	static uint32_t GetLightCount() { return s_LightCount; }
	static uint32_t GetShadowCasters() { return s_ShadowCasters; }

};

void BindLights(const std::vector<PointLight>& pointLights, const std::shared_ptr<Shader>& shader);
