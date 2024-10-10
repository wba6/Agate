#include "Texture.h"
#include <glad/glad.h>
#include "OpenGLCheck.h"
#include <SOIL2/SOIL2.h>
#include <iostream>
#include <filesystem>
#include <algorithm>

#define KHRONOS_STATIC
#include <ktx.h>

namespace Agate {

// Function to create a normalized path with forward slashes
    std::string create_normalized_path(const std::string& directory, const std::string& relative_path) {
        std::filesystem::path dir_path(directory);
        std::filesystem::path rel_path(relative_path);
        std::filesystem::path combined_path = dir_path / rel_path;
        return combined_path.generic_string();
    }

// Helper function to convert string to lowercase
    std::string to_lowercase(const std::string& str) {
        std::string lower = str;
        std::transform(lower.begin(), lower.end(), lower.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        return lower;
    }

// Function to load KTX texture using libktx
    bool load_ktx_with_libktx(const std::string& filename, GLuint& textureID, GLenum& target, int& width, int& height) {
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
        std::cout << "Successfully loaded KTX texture: " << filename << std::endl;
        return true;
    }

// Helper function to load KTX files using libktx
    bool load_ktx_texture(const std::string& filename, GLuint& textureID, GLenum& target, int& width, int& height) {
        return load_ktx_with_libktx(filename, textureID, target, width, height);
    }

// Helper function to load standard images using SOIL2
    bool load_standard_texture(const std::string& filename, GLuint& textureID, GLenum& target, int& width, int& height) {
        // Load texture using SOIL2
        textureID = SOIL_load_OGL_texture(
                filename.c_str(),
                SOIL_LOAD_AUTO,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
        );

        if (textureID == 0) {
            std::cerr << "SOIL2 failed to load texture at path: " << filename << ". Error: " << SOIL_last_result() << std::endl;
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
            std::cerr << "OpenGL error after setting texture parameters for " << filename << ": " << error << std::endl;
            glBindTexture(target, 0);
            return false;
        }

        // Unbind the texture
        glBindTexture(target, 0);

        return true;
    }

    Texture::Texture(const char *file, std::string &directory, int pixelFormat)
            : m_width(0), m_height(0), m_path(file), m_type("texture"), m_target(GL_TEXTURE_2D) {
        std::string normalizedPath = create_normalized_path(directory, m_path);
        std::filesystem::path filepath(normalizedPath);
        std::string extension = to_lowercase(filepath.extension().string());

        if (extension == ".ktx" || extension == ".ktx2") {
            // Load KTX file using libktx
            if (!load_ktx_texture(normalizedPath, m_textureID, m_target, m_width, m_height)) {
                std::cerr << "Failed to load KTX texture at path: " << normalizedPath << std::endl;
                // Optionally, set a default texture or handle the error gracefully
            }
        } else {
            // Load standard image using SOIL2
            if (!load_standard_texture(normalizedPath, m_textureID, m_target, m_width, m_height)) {
                std::cerr << "Failed to load standard texture at path: " << normalizedPath << std::endl;
                // Optionally, set a default texture or handle the error gracefully
            }
        }
    }

    void Texture::bind(unsigned int slot) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(m_target, m_textureID);
    }

    void Texture::unBind() {
        glBindTexture(m_target, 0);
    }

    const std::string &Texture::getPath() {
        return m_path;
    }

    const std::string &Texture::getType() {
        return m_type;
    }

    void Texture::setType(std::string &typeName) {
        m_type = typeName;
    }

} // namespace Agate
