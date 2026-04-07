#include "TextureUser.hpp"
#include "Rendering/Renderer.hpp"

namespace Agate {

    TextureUser::TextureUser(const char *file, const std::string &directory)
    : m_path(file), m_directory(directory), m_UUID(UUID::Generate()) {
        Renderer::Submit(std::make_unique<CreateTexture>(*this));
    }

    TextureUser::TextureUser(TextureUser&& other) noexcept
    : m_path(std::move(other.m_path)), m_directory(std::move(other.m_directory)), m_type(std::move(other.m_type)), m_UUID(other.m_UUID) {
        other.m_UUID = UUID();
    }

    TextureUser& TextureUser::operator=(TextureUser&& other) noexcept {
        if (this != &other) {
            // If this object already manages a resource, delete it
            if (m_UUID) {
                Renderer::Submit(std::make_unique<DeleteTexture>(m_UUID));
            }

            m_path = std::move(other.m_path);
            m_directory = std::move(other.m_directory);
            m_type = std::move(other.m_type);
            m_UUID = other.m_UUID;

            other.m_UUID = UUID();
        }
        return *this;
    }

    void TextureUser::bind(unsigned int slot) const {
        if (m_UUID) {
            Renderer::Submit(std::make_unique<BindTexture>(m_UUID, slot));
        }
    }

    TextureUser::~TextureUser() {
        if (m_UUID) {
            Renderer::Submit(std::make_unique<DeleteTexture>(m_UUID));
        }
    }

}
