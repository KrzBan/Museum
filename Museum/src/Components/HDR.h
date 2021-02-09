#pragma once

#include <iostream>
#include "Shader.h";

class HDR {

	uint32_t m_Width;
	uint32_t m_Height;

	uint32_t m_HDRFbo;
	uint32_t m_ColorBuffer;
	uint32_t m_RboDepth;
public:
	HDR(uint32_t width, uint32_t height);
	~HDR();

	void BindFramebuffer();
	void UnbindFramebuffer();

	void BindTexture(const std::shared_ptr<Shader>& shader);
};
