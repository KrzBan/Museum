#pragma once

#include <iostream>

struct ShadowMap {

	unsigned int depthCubemaps;
	unsigned int depthMapFBO;

	uint32_t m_Width;
	uint32_t m_Height;

	ShadowMap(uint32_t width, uint32_t height, uint32_t lightSourceCount);
	~ShadowMap();

	void Bind();
	void Unbind();

};
