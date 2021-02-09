#pragma once

#include <iostream>

#include "Utility.h"
#include "stb/stb_image.h"

class Texture {
private:
	unsigned int m_ID;
	int m_Width, m_Height, m_BPP;
	GLenum m_InternalFormat, m_DataFormat;
	std::string m_Path;
	std::string m_Type;
public:
	Texture(std::string path);

	~Texture();

	void Bind(uint32_t slot = 0);
	void Unbind();

	void SetData(void* data, uint32_t size);

	int GetWidth()const{ return m_Width; };
	int GetHeight()const { return m_Height; };

	void SetType(const std::string& str) {m_Type = str; }
	void SetPath(const std::string& str) {m_Path = str; }

	std::string GetType() const { return m_Type; }
	std::string GetPath() const { return m_Path; }

	bool operator==(const Texture& other);
};