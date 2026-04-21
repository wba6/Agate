/**
 * @brief FrameBuffer implementation
 */

#include "FrameBuffer.hpp"
#include "Core/Logger.h"
#include <glad/glad.h>  

namespace Agate {

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
        : m_width(width), m_height(height) {

    glGenFramebuffers(1, &m_fbo);
    GenerateTextureAttachment();
    GenerateRenderBufferAttachment();
    if (!Complete()) {
        PRINTCRIT("Failed to create FrameBuffer");
    }
}

FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &m_fbo);
    m_fbo = 0;
    DeleteTextureAttachment();
    DeleteRenderBufferAttachment();
}

void FrameBuffer::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void FrameBuffer::UnBind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Resize(unsigned int width, unsigned int height) {
    m_width = width;
    m_height = height;
}

void FrameBuffer::GenerateTextureAttachment() {

    // Generate Texture
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Bind Texture to FBO
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::DeleteTextureAttachment() {
    glDeleteTextures(1, &m_texture);
    m_texture = 0;
}

void FrameBuffer::GenerateRenderBufferAttachment() {

    // Generate Render Buffer
    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    // Bind Render Buffer to FBO
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::DeleteRenderBufferAttachment() {
    glDeleteRenderbuffers(1, &m_rbo);
    m_rbo = 0;
}

bool FrameBuffer::Complete() const {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return status == GL_FRAMEBUFFER_COMPLETE;

} // namespace Agate
