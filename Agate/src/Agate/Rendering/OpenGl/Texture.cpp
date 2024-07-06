#include "Texture.h"
#include <glad/glad.h>

//This has to be the final include with this definition here
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <Core/Logger.h>

namespace Agate {
    Texture::Texture(const char *file, std::string &directory, int pixelFormat)
            : m_width(0), m_height(0), m_path(file), m_type("texture") {
        std::string filename = directory + '/' + m_path;

        //because of the way the texture we have is loaded
        stbi_set_flip_vertically_on_load(true);

        glGenTextures(1, &m_textureID);

        int nrComponents;
        unsigned char *data = stbi_load(filename.c_str(), &m_width, &m_height, &nrComponents, 0);
        if (data) {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;
            else
                PRINTERROR("Texture::Texture unknown nrComponents type");

            glBindTexture(GL_TEXTURE_2D, m_textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
            glBindTexture(GL_TEXTURE_2D, 0);
        } else {
            PRINTERROR(std::string("Texture failed to load at path: ") + m_path)
            glBindTexture(GL_TEXTURE_2D, 0);
            stbi_image_free(data);
        }
    }

    void Texture::bind(unsigned int slot = 0) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
    }

    void Texture::unBind(unsigned int slot = 0) {
        glBindTexture(GL_TEXTURE_2D, 0);
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
}