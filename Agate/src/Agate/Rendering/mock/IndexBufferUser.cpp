#include "IndexBufferUser.hpp"
#include "Rendering/Renderer.hpp"

namespace Agate {

    IndexBufferUser::IndexBufferUser(std::vector<unsigned int> &vector, UUID VAOUUID)
        : m_indinces(vector), m_VAOUUID(VAOUUID) {
        Renderer::Submit(std::make_unique<CreateIndexBuffer>(*this, m_VAOUUID));
    }

    void IndexBufferUser::Bind() const {
        Renderer::Submit(std::make_unique<BindIndexBuffer>(m_UUID));
    }

    void IndexBufferUser::UnBind() const {
        Renderer::Submit(std::make_unique<UnBindIndexBuffer>());
    }

    unsigned int IndexBufferUser::GetNumOfIndices() const {
        return m_indinces.size();
    }

    IndexBufferUser::~IndexBufferUser() {
    }

}
