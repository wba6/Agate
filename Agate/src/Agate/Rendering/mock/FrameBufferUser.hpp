/**
 * @brief Include file for FrameBufferUser - A mock class for creating FBOs
 *        on the render thread
 */

#ifndef AGATE_FRAMEBUFFERUSER_HPP
#define AGATE_FRAMEBUFFERUSER_HPP

#include "Agate/Rendering/UUID.hpp"

namespace Agate {

class FrameBufferUser {
public:
    /**
     * 
     */
    explicit FrameBufferUser(unsigned int width, unsigned int height);

    /**
    * @brief Destroys the FrameBufferUser.
    */
    ~FrameBufferUser();

    // Disable copying
    FrameBufferUser(const FrameBufferUser&) = delete;
    FrameBufferUser& operator=(const FrameBufferUser&) = delete;

    // Enable move semantics
    FrameBufferUser(FrameBufferUser&& other) noexcept;
    FrameBufferUser& operator=(FrameBufferUser&& other) noexcept;

    /**
     * @brief Gets the width of the framebuffer.
     * @return The width of the framebuffer.
     */
    unsigned int getWidth() const { return m_width; }

    /**
     * @brief Gets the height of the framebuffer.
     * @return The height of the framebuffer.
     */
    unsigned int getHeight() const { return m_height; }

    /**
     * @brief Gets the UUID of this FrameBuffer.
     * @return The UUID of the framebuffer.
     */
    UUID getUUID() const { return m_UUID; }

    /**
     * @brief Binds the framebuffer for rendering
     * 
     * Enqueues a command to bind the underlying OpenGL buffers
     */
    void Bind() const;

    /**
     * @brief Unbinds the framebuffer
     * 
     * Enqueues a command to unbind the underlying OpenGL buffers
     */
    void UnBind() const;

    /**
     * @brief Resizes the framebuffer to the specified dimensions
     * 
     * Enqueues a command to resize the underlying OpenGL buffers and update the stored dimensions
     */
    void Resize(unsigned int width, unsigned int height);

private:
    unsigned int m_width;
    unsigned int m_height;
    UUID m_UUID;
};

} // namespace Agate

#endif
