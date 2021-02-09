#include "HDR.h"

#include "Utility.h"

HDR::HDR(uint32_t width, uint32_t height) : m_Width{ width }, m_Height{ height } {
    glGenFramebuffers(1, &m_HDRFbo);
    // create floating point color buffer
    glGenTextures(1, &m_ColorBuffer);
    glBindTexture(GL_TEXTURE_2D, m_ColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // create depth buffer (renderbuffer)
    glGenRenderbuffers(1, &m_RboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    // attach buffers
    glBindFramebuffer(GL_FRAMEBUFFER, m_HDRFbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorBuffer, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RboDepth);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void HDR::BindFramebuffer() {
    SetFrameSize(m_Width, m_Height);
    glBindFramebuffer(GL_FRAMEBUFFER, m_HDRFbo);
    ClearScreen();
}
void HDR::UnbindFramebuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void HDR::BindTexture(const std::shared_ptr<Shader>& shader) {
    glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D, m_ColorBuffer);
    shader->SetInt("textureHDR", 7);
}

HDR::~HDR() {
	glDeleteFramebuffers(1, &m_HDRFbo);
	glDeleteTextures(1, &m_ColorBuffer);
    glDeleteRenderbuffers(1, &m_RboDepth);
}