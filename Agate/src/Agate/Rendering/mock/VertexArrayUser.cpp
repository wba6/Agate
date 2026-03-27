#include "VertexArrayUser.hpp"
#include "Rendering/Renderer.hpp"

namespace Agate {

    VertexArrayUser::VertexArrayUser(BufferDataLayout bufferInformation, std::shared_ptr<void> data, size_t data_size)
    : m_bufferInformation(bufferInformation), m_data(data), m_dataSize(data_size) {
        Renderer::Submit(std::make_unique<CreateVertexArray>(*this));
    }

    void VertexArrayUser::Bind() const {
        Renderer::Submit(std::make_unique<BindVertexArray>(m_UUID));
    }

    void VertexArrayUser::UnBind() const {
        Renderer::Submit(std::make_unique<UnBindVertexArray>());
    }

    VertexArrayUser::~VertexArrayUser() {
        Renderer::Submit(std::make_unique<DeleteVertexArray>(m_UUID));
    }

}
