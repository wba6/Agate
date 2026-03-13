#ifndef AGATE_TEXTUREUSER_HPP
#define AGATE_TEXTUREUSER_HPP

#include <string>
#include "Rendering/UUID.hpp"

namespace Agate {
    class TextureUser {
    public:
        TextureUser(const char *file, const std::string &directory)
            : m_path(file), m_directory(directory) {}

        const std::string& getPath() const { return m_path; }
        const std::string& getDirectory() const { return m_directory; }
        UUID getUUID() const { return m_UUID; }

    private:
        std::string m_path;
        std::string m_directory;
        UUID m_UUID;
    };
}

#endif//AGATE_TEXTUREUSER_HPP
