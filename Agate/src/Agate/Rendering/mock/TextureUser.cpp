#include "TextureUser.hpp"
#include "Rendering/Renderer.hpp"
#include "Agate/Async/TaskPool.h"
#include "Agate/Core/Logger.h"
#include <iterator>
#include <fstream>
#include <filesystem>

namespace Agate {

    TextureUser::TextureUser(const char *file, const std::string &directory)
    : m_path(file), m_directory(directory), m_UUID(UUID::Generate()) {
        auto task_handle = Agate::TaskPool::Enqueue([path = m_path, dir = m_directory]() -> std::string {
            std::filesystem::path full_path = std::filesystem::path(dir) / std::filesystem::path(path);
            std::ifstream in(full_path, std::ios::binary);
            if (!in) {
                PRINTERROR("Failed to open texture file: {}", full_path.string());
                return "";
            }
            // we are passing this string around alot this is inefficient
            std::string str((std::istreambuf_iterator<char>(in)),
                        std::istreambuf_iterator<char>());
            return std::move(str);
        }).Then([ID = m_UUID](std::string result) -> void {
            if (!result.empty()) {
                Renderer::Submit(std::make_unique<CreateTexture>(std::move(result), ID));
            }
        });
    }

    TextureUser::TextureUser(TextureUser&& other) noexcept
    : m_path(std::move(other.m_path)), m_directory(std::move(other.m_directory)), m_UUID(other.m_UUID) {
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
