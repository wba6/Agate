#include "Texture.h"
#include <glad/glad.h>
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
     * Helper function to load KTX texture using libktx
     *
     * @param filename: The path to the KTX file
     * @param textureID: The texture ID to bind the texture to
     * @param target: The texture target
     * @param width: The width of the texture
     * @param height: The height of the texture
     *
     * @return True if the texture was loaded successfully, false otherwise
     */
    bool Texture::load_ktx_with_libktx(const std::string& filename, unsigned int& textureID, unsigned int& target, int& width, int& height) {
        // Load texture data
        ktxTexture* kTexture;
        KTX_error_code ktxerror = ktxTexture_CreateFromNamedFile(filename.c_str(),
                                                                 KTX_TEXTURE_CREATE_NO_FLAGS,
                                                                 &kTexture);
        if (ktxerror != KTX_SUCCESS) {
            PRINTERROR("Failed to read texture file: {} {}\n", filename, ktxErrorString(ktxerror));
            return false;
        }
        GLenum GLTarget, GLError;
        ktxerror = ktxTexture_GLUpload(kTexture, &textureID, &GLTarget, &GLError);
        if (ktxerror != KTX_SUCCESS) {
            PRINTERROR("Failed to upload texture file: {} {}\n", filename, ktxErrorString(ktxerror));
            return false;
        }

        // Generate mipmaps
        if (kTexture->numLevels == 1)
            glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Unbind texture and destroy ktxTexture
        glBindTexture(target, 0);
        ktxTexture_Destroy(kTexture);
        PRINTMSG("Successfully loaded KTX texture: {}", filename);
        return true;
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
    bool Texture::load_standard_texture_with_soil2(const std::string& filename, unsigned int& textureID, unsigned int& target, int& width, int& height) {
        // Load texture using SOIL2
        textureID = SOIL_load_OGL_texture(
                filename.c_str(),
                SOIL_LOAD_AUTO,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
        );

        if (textureID == 0) {
            PRINTERROR("SOIL2 failed to load texture at path: {}. Error: {}", filename, SOIL_last_result());
            return false;
        }

        // Assume GL_TEXTURE_2D for standard images
        target = GL_TEXTURE_2D;

        // Retrieve texture dimensions
        glBindTexture(target, textureID);
        glGetTexLevelParameteriv(target, 0, GL_TEXTURE_WIDTH, &width);
        glGetTexLevelParameteriv(target, 0, GL_TEXTURE_HEIGHT, &height);

        // Set texture parameters
        glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Check for errors
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            PRINTERROR("OpenGL error after setting texture parameters for {}, {}", filename, error);
            glBindTexture(target, 0);
            return false;
        }

        // Unbind the texture
        glBindTexture(target, 0);

        return true;
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

    }

    Texture::~Texture() {
        glDeleteTextures(1, &m_textureID);
    }

    /*
     * Bind the texture to a texture unit
     *
     * @param slot: The texture unit to bind the texture to
     *
     * @return void
     */
    void Texture::bind(unsigned int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(m_target, m_textureID);
    }

    /*
     * Unbind the texture
     *
     * @return void
     */
    void Texture::unBind() const {
        glBindTexture(m_target, 0);
    }

    /*
     * Get the path of the texture
     *
     * @return The path of the texture
     */
    const std::string &Texture::getPath() {
        return m_path;
    }

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

    void Texture::initialize() {
        std::string normalizedPath = create_normalized_path(m_directory, m_path);
        std::filesystem::path filepath(normalizedPath);

        // Convert extension to lowercase
        std::string extension = filepath.extension().string();
        std::transform(extension.begin(), extension.end(), extension.begin(),
                                              [](unsigned char c){ return std::tolower(c); });
        if (extension == ".ktx" || extension == ".ktx2") {
            // Load KTX file using libktx
            if (!load_ktx_with_libktx(normalizedPath, m_textureID, m_target, m_width, m_height)) {
                PRINTERROR("Failed to load KTX texture at path: {}", normalizedPath);
                // Optionally, set a default texture or handle the error gracefully @TODO
            }
        } else {
            // Load standard image using SOIL2
            if (!load_standard_texture_with_soil2(normalizedPath, m_textureID, m_target, m_width, m_height)) {
                PRINTERROR("Failed to load standard texture at path: {}", normalizedPath);
                // Optionally, set a default texture or handle the error gracefully @TODO
            }
        }
    }

} // namespace Agate
