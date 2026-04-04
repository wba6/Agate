#include "VertexArrayUser.hpp"
#include "Rendering/Renderer.hpp"

namespace Agate {

    VertexArrayUser::VertexArrayUser(BufferDataLayout bufferInformation, std::shared_ptr<void> data, size_t data_size)
    : m_UUID(UUID::Generate()), m_bufferInformation(bufferInformation), m_data(data), m_dataSize(data_size) {
        Renderer::Submit(std::make_unique<CreateVertexArray>(*this));
    }

    VertexArrayUser::VertexArrayUser(VertexArrayUser&& other) noexcept
    : m_UUID(other.m_UUID), m_bufferInformation(std::move(other.m_bufferInformation)),
      m_data(std::move(other.m_data)), m_dataSize(other.m_dataSize) {
        other.m_UUID = UUID();
    }

    VertexArrayUser& VertexArrayUser::operator=(VertexArrayUser&& other) noexcept {
        if (this != &other) {
            // If this object already manages a resource, delete it
            if (m_UUID) {
                Renderer::Submit(std::make_unique<DeleteVertexArray>(m_UUID));
            }

            m_UUID = other.m_UUID;
            m_bufferInformation = std::move(other.m_bufferInformation);
            m_data = std::move(other.m_data);
            m_dataSize = other.m_dataSize;

            other.m_UUID = UUID();
        }
        return *this;
    }

    void VertexArrayUser::Bind() const {
        if (m_UUID) {
            Renderer::Submit(std::make_unique<BindVertexArray>(m_UUID));
        }
    }

    void VertexArrayUser::UnBind() const {
        Renderer::Submit(std::make_unique<UnBindVertexArray>());
    }

    VertexArrayUser::~VertexArrayUser() {
        if (m_UUID) {
            Renderer::Submit(std::make_unique<DeleteVertexArray>(m_UUID));
        }
    }

}
