#include "Light.h"

uint32_t PointLight::s_LightCount = 0;
uint32_t PointLight::s_ShadowCasters = 0;

void BindLights(const std::vector<PointLight>& pointLights, const std::shared_ptr<Shader>& shader) {
	size_t i = 0;
	shader->Bind();
	for (auto& light : pointLights) {
		shader->SetFloat3("u_PointLights[" + std::to_string(i) + "].ambient", light.ambient);
		shader->SetFloat3("u_PointLights[" + std::to_string(i) + "].diffuse", light.diffuse);
		shader->SetFloat3("u_PointLights[" + std::to_string(i) + "].specular", light.specular);
		shader->SetFloat3("u_PointLights[" + std::to_string(i) + "].position", light.position);
		shader->SetBool("u_PointLights[" + std::to_string(i) + "].castsShadows", light.castsShadows);
		++i;
	}
}