#include "TextureUser.hpp"
#include "Rendering/Renderer.hpp"

namespace Agate {

    TextureUser::TextureUser(const char *file, const std::string &directory)
        : m_path(file), m_directory(directory) {
        Renderer::Submit(std::make_unique<CreateTexture>(*this));
    }

    void TextureUser::bind(unsigned int slot) const {
        Renderer::Submit(std::make_unique<BindTexture>(m_UUID, slot));
    }

    TextureUser::~TextureUser() {
        Renderer::Submit(std::make_unique<DeleteTexture>(m_UUID));
    }

}
