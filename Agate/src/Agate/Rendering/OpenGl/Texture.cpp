#include "Texture.h"
#include <cstddef>
#include <glad/glad.h>
#include "Core/Logger.h"
#include "OpenGLCheck.h"
#include <SOIL2/SOIL2.h>
#include <iostream>
#include <filesystem>
#include <algorithm>

#include <ktx.h>

namespace Agate {

    /*
     * Helper function to create a normalized path from a directory and a relative path
     *
     * @param directory: The directory path
     * @param relative_path: The relative path
     *
     * @return The normalized path
     */
    std::string create_normalized_path(const std::string& directory, const std::string& relative_path) {
        std::filesystem::path dir_path(directory);
        std::filesystem::path rel_path(relative_path);
        std::filesystem::path combined_path = dir_path / rel_path;
        return combined_path.generic_string();
    }

    /*
     * Helper function to load standard images using SOIL2
     *
     * @param filename: The path to the image file
     * @param textureID: The texture ID to bind the texture to
     * @param target: The texture target
     * @param width: The width of the texture
     * @param height: The height of the texture
     *
     * @return True if the texture was loaded successfully, false otherwise
     */
    unsigned int Texture::load_standard_texture_with_soil2(const std::string& filename) {
        // Load texture using SOIL2
        unsigned int textureID;
        textureID = SOIL_load_OGL_texture(
                filename.c_str(),
                SOIL_LOAD_AUTO,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
        );

        if (textureID == 0) {
            PRINTERROR("SOIL2 failed to load texture at path: {}. Error: {}", filename, SOIL_last_result());
        }
        return textureID;
    }
    
    unsigned int Texture::loadTextureFromMemory(const unsigned char* data, size_t dataLength) {
        // Load texture using SOIL2
        unsigned int textureID;
        textureID = SOIL_load_OGL_texture_from_memory(
                data,
                dataLength,
                SOIL_LOAD_AUTO,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
        );
        return textureID;
    }

    void Texture::configureTexture() {
        // Retrieve texture dimensions
        GLCall(glBindTexture(m_target, m_textureID));
        GLCall(glGetTexLevelParameteriv(m_target, 0, GL_TEXTURE_WIDTH, &m_width));
        GLCall(glGetTexLevelParameteriv(m_target, 0, GL_TEXTURE_HEIGHT, &m_height));

        // Set texture parameters
        GLCall(glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GLCall(glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GLCall(glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
        GLCall(glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        // Unbind the texture
        GLCall(glBindTexture(m_target, 0));

    }

    /*
     * Constructor for Texture class
     *
     * @param file: The path to the texture file
     * @param directory: The directory path
     *
     * @return A Texture object
     */
    Texture::Texture(const char *file, const std::string &directory)
            : m_width(0), m_height(0), m_path(file), m_type("texture"), m_target(GL_TEXTURE_2D), m_textureID(0), m_directory(directory) {
        m_textureID = this->createTexture();
        
        if (m_textureID != 0) {
            this->configureTexture();
        }

    }

    Texture::Texture(const unsigned char *data, size_t dataLength)
            : m_width(0), m_height(0), m_path(), m_type("texture"), m_target(GL_TEXTURE_2D), m_textureID(0), m_directory() {
        m_textureID = this->createTexture(data, dataLength);

        if (m_textureID != 0) {
            this->configureTexture();
        }
    };

    /*
     * Get the type of the texture
     *
     * @return The type of the texture
     */
    const std::string &Texture::getType() {
        return m_type;
    }

    /*
     * Set the type of the texture
     *
     * @param typeName: The type of the texture
     *
     * @return void
     */
    void Texture::setType(std::string &typeName) {
        m_type = typeName;
    }

    Texture::~Texture() {
        GLCall(glDeleteTextures(1, &m_textureID));
    }

    /*
     * Bind the texture to a texture unit
     *
     * @param slot: The texture unit to bind the texture to
     *
     * @return void
     */
    void Texture::bind(unsigned int slot) const {
        GLCall(glActiveTexture(GL_TEXTURE0 + slot));
        GLCall(glBindTexture(m_target, m_textureID));
    }

    /*
     * Unbind the texture
     *
     * @return void
     */
    void Texture::unBind() const {
        GLCall(glBindTexture(m_target, 0));
    }

    unsigned int Texture::createTexture() {
        unsigned int textureID = 0;

        // Load from file path
        if (!(m_directory.empty() || m_path.empty())) {
            std::string normalizedPath = create_normalized_path(m_directory, m_path);
            std::filesystem::path filepath(normalizedPath);

            // Convert extension to lowercase
            std::string extension = filepath.extension().string();
            std::transform(extension.begin(), extension.end(), extension.begin(),
                                              [](unsigned char c){ return std::tolower(c); });

            // Load standard image using SOIL2
            textureID = load_standard_texture_with_soil2(normalizedPath);
            if (textureID == 0) {
                PRINTERROR("Failed to load standard texture at path: {}", normalizedPath);
                // Optionally, set a default texture or handle the error gracefully @TODO
            }
        }

        if(textureID == 0) { PRINTERROR("Failed to load texture from file");}
        return textureID;
    }

    unsigned int Texture::createTexture(const unsigned char* data, size_t dataLength) {
        if(data == nullptr){
            PRINTERROR("Failed to load texture becuase no data was provided");
            return 0;
        }

        unsigned int textureID{loadTextureFromMemory(data, dataLength)};

        if(textureID == 0){
            PRINTERROR("Failed to load texture from memeory");
        }
        return textureID;

    }

} // namespace Agate
