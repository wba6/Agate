#ifndef AGATE_TEXTUREUSER_HPP
#define AGATE_TEXTUREUSER_HPP

#include <string>
#include "Agate/Rendering/UUID.hpp"

namespace Agate {
    class TextureUser {
    public:
        TextureUser(const char *file, const std::string &directory);

        const std::string& getPath() const { return m_path; }
        const std::string& getDirectory() const { return m_directory; }
        const std::string& getType() const { return m_type; }
        void setType(const std::string& type) { m_type = type; }
        UUID getUUID() const { return m_UUID; }

        void bind(unsigned int slot = 0) const;

    private:
        std::string m_path;
        std::string m_directory;
        std::string m_type;
        UUID m_UUID;
    };
}

#endif//AGATE_TEXTUREUSER_HPP
