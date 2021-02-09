#include "Texture.h"

#include <cassert>
#include <algorithm>

Texture::Texture(std::string path):m_ID(0), m_Width(0), m_Height(0), m_BPP(0){
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    stbi_set_flip_vertically_on_load(true);
    stbi_uc* m_Data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);

    GLenum internalFormat = 0, dataFormat = 0;
    switch (m_BPP) {
        case 1:	dataFormat = GL_RED; internalFormat = GL_RED;    break;
        case 2: dataFormat = GL_RG; internalFormat = GL_RG8;     break;
        case 3: dataFormat = GL_RGB; internalFormat = GL_RGB8;    break;
        case 4: dataFormat = GL_RGBA; internalFormat = GL_RGBA8;   break;
            
    }
    m_InternalFormat = internalFormat;
    m_DataFormat = dataFormat;
    
    if (m_Data)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  //to load data with weird width and heights
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, m_Data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        m_Width = m_Height = m_BPP = 0;

        size_t pathIndex = path.find_last_of("/");
        if (pathIndex == std::string::npos) pathIndex = 0;
        std::cout << "Failed to load texture: "<< path.substr(pathIndex) << '\n';
    }
    stbi_image_free(m_Data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_ID);
}

void Texture::Bind(uint32_t slot){
	glActiveTexture(GL_TEXTURE0+slot);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Unbind(){
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetData(void* data, uint32_t size) {
    assert(size == m_Width * m_Height * m_BPP && "Wrong texture size!");

    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
}

bool Texture::operator==(const Texture& other)
{
    return m_ID == other.m_ID;
}


