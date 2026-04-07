#ifndef AGATE_TEXTUREUSER_HPP
#define AGATE_TEXTUREUSER_HPP

#include <string>
#include "Agate/Rendering/UUID.hpp"

namespace Agate {
    /**
     * @brief A mock representation of an OpenGL Texture for use on the main thread.
     *
     * TextureUser stores texture file paths, metadata, and associated UUIDs
     * to allow the application to interact with textures without
     * directly making OpenGL calls.
     */
    class TextureUser {
    public:
        /**
         * @brief Constructs a TextureUser.
         *
         * @param file The path to the texture file.
         * @param directory The directory path for the texture.
         */
        TextureUser(const char *file, const std::string &directory);

        // Disable copying
        TextureUser(const TextureUser&) = delete;
        TextureUser& operator=(const TextureUser&) = delete;

        // Enable move semantics
        TextureUser(TextureUser&& other) noexcept;
        TextureUser& operator=(TextureUser&& other) noexcept;

        /**
         * @brief Gets the path to the texture file.
         * @return The texture file path.
         */
        const std::string& getPath() const { return m_path; }

        /**
         * @brief Gets the directory for the texture.
         * @return The directory path.
         */
        const std::string& getDirectory() const { return m_directory; }

        /**
         * @brief Gets the type of the texture.
         * @return The texture type.
         */
        const std::string& getType() const { return m_type; }

        /**
         * @brief Sets the type of the texture.
         * @param type The new texture type.
         */
        void setType(const std::string& type) { m_type = type; }

        /**
         * @brief Gets the UUID of this Texture.
         * @return The UUID of the texture.
         */
        UUID getUUID() const { return m_UUID; }

        /**
         * @brief Binds the texture.
         *
         * Enqueues a command to bind the underlying OpenGL texture to a given slot.
         *
         * @param slot The texture unit slot to bind to.
         */
        void bind(unsigned int slot = 0) const;

        /**
         * @brief Destroys the TextureUser.
         */
        ~TextureUser();

    private:
        std::string m_path;
        std::string m_directory;
        std::string m_type;
        UUID m_UUID;
    };
}

#endif//AGATE_TEXTUREUSER_HPP
