#pragma once

#include "Utility.h"

class Shader
{
public:
	Shader(const std::string& name, const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

	const std::string& GetName() const { return m_Name; }

	void Bind() const;

	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetIntArray(const std::string& name, int* values, uint32_t count) const;
	void SetFloat(const std::string& name, float value) const;
	void SetFloat2(const std::string& name, const glm::vec2&) const;
	void SetFloat3(const std::string& name, const glm::vec3&) const;
	void SetFloat4(const std::string& name, const glm::vec4&) const;
	void SetMat4f(const std::string& name,const glm::mat4& mat)const;
private:
	void LightParse(std::string& code, uint32_t lightCount, uint32_t shadowCount);

private:
	uint32_t ID;
	const std::string m_Name;
};
