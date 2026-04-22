/**
 * @brief FrameBufferUser implementation
 */

#include "FrameBufferUser.hpp"
#include "Rendering/Renderer.hpp"

namespace Agate {

FrameBufferUser::FrameBufferUser(unsigned int width, unsigned int height)
        : m_width(width), m_height(height), m_UUID(UUID::Generate()) {

    Renderer::Submit(std::make_unique<CreateFrameBuffer>(*this));
}

FrameBufferUser::FrameBufferUser(FrameBufferUser&& other) noexcept
        : m_width(other.m_width), m_height(other.m_height), m_UUID(other.m_UUID) {

    other.m_UUID = UUID();
}

FrameBufferUser& FrameBufferUser::operator=(FrameBufferUser&& other) noexcept {
    if (this != &other) {
        // If this object already manages a resource, delete it
        if (m_UUID) {
            Renderer::Submit(std::make_unique<DeleteFrameBuffer>(m_UUID));
        }

        m_width = other.m_width;
        m_height = other.m_height;
        m_UUID = other.m_UUID;

        other.m_UUID = UUID();
    }
    return *this;
}

FrameBufferUser::~FrameBufferUser() {
    if (m_UUID) {
        Renderer::Submit(std::make_unique<DeleteFrameBuffer>(m_UUID));
    }
}

void FrameBufferUser::Bind() const {
    if (m_UUID) {
        Renderer::Submit(std::make_unique<BindFrameBuffer>(m_UUID));
    }
}

void FrameBufferUser::UnBind() const {
    Renderer::Submit(std::make_unique<UnBindFrameBuffer>());
}

void FrameBufferUser::Resize(unsigned int width, unsigned int height) {
    if (m_UUID) {
        Renderer::Submit(std::make_unique<ResizeFrameBuffer>(m_UUID, width, height));
        m_width = width;
        m_height = height;
    }
}

} // namespace Agate
