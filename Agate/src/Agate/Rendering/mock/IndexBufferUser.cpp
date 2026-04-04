#include "IndexBufferUser.hpp"
#include "Rendering/Renderer.hpp"

namespace Agate {

    IndexBufferUser::IndexBufferUser(std::vector<unsigned int> &vector, UUID VAOUUID)
    : m_indinces(vector), m_VAOUUID(VAOUUID), m_UUID(UUID::Generate()) {
        Renderer::Submit(std::make_unique<CreateIndexBuffer>(*this, m_VAOUUID));
    }

    IndexBufferUser::IndexBufferUser(IndexBufferUser&& other) noexcept
    : m_indinces(std::move(other.m_indinces)), m_VAOUUID(other.m_VAOUUID), m_UUID(other.m_UUID) {
        other.m_UUID = UUID();
    }

    IndexBufferUser& IndexBufferUser::operator=(IndexBufferUser&& other) noexcept {
        if (this != &other) {
            // If this object already manages a resource, delete it
            if (m_UUID) {
                Renderer::Submit(std::make_unique<DeleteIndexBuffer>(m_UUID));
            }

            m_indinces = std::move(other.m_indinces);
            m_VAOUUID = other.m_VAOUUID;
            m_UUID = other.m_UUID;

            other.m_UUID = UUID();
        }
        return *this;
    }

    void IndexBufferUser::Bind() const {
        if (m_UUID) {
            Renderer::Submit(std::make_unique<BindIndexBuffer>(m_UUID));
        }
    }

    void IndexBufferUser::UnBind() const {
        Renderer::Submit(std::make_unique<UnBindIndexBuffer>());
    }

    unsigned int IndexBufferUser::GetNumOfIndices() const {
        return static_cast<unsigned int>(m_indinces.size());
    }

    IndexBufferUser::~IndexBufferUser() {
        if (m_UUID) {
            Renderer::Submit(std::make_unique<DeleteIndexBuffer>(m_UUID));
        }
    }

}
