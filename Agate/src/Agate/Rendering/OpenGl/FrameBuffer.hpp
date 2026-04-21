/**
 * @brief Include file for the FrameBuffer (FBO) class
 */

#ifndef AGATE_FRAMEBUFFER_HPP
#define AGATE_FRAMEBUFFER_HPP

namespace Agate {

class FrameBuffer {
public:
    FrameBuffer(unsigned int width, unsigned int height);
    ~FrameBuffer();
    void Bind();
    void UnBind();
    void Resize(unsigned int width, unsigned int height);
private:
    void GenerateTextureAttachment();
    void DeleteTextureAttachment();
    void GenerateRenderBufferAttachment();
    void DeleteRenderBufferAttachment();
    bool Complete() const;
    unsigned int m_fbo{ 0 };
    unsigned int m_rbo{ 0 };
    unsigned int m_texture{ 0 };
    unsigned int m_width;
    unsigned int m_height;
};

} // namespace Agate

#endif
