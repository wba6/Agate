//
// Created by William Aey on 7/27/2022.
//

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include <cstddef>
namespace Agate {
    class Texture {
    public:
        /*
        * Constructor for Texture class
        *
        * @param file: The path to the texture file
        * @param directory: The directory path
        *
        * @return A Texture object
        */
        Texture(const char *file, const std::string &directory);
        Texture(const unsigned char *data, size_t dataLength);

        virtual ~Texture();

        /*
        * Bind the texture to a texture unit
        *
        * @param slot: The texture unit to bind the texture to
        *
        * @return void
        */
        void bind(unsigned int slot) const;

        /*
        * Unbind the texture
        *
        * @return void
        */
        void unBind() const;

        /*
        * Set the type of the texture
        *
        * @param typeName: The type of the texture
        *
        * @return void
        */
        void setType(std::string &typeName);

        /*
        * Get the type of the texture
        *
        * @return The type of the texture
        */
        const std::string &getType();
        
    private:

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
        unsigned int load_standard_texture_with_soil2(const std::string& filename);

        void configureTexture();

        unsigned int createTexture(); 
        unsigned int createTexture(const unsigned char* data, size_t dataLength); 

        unsigned int loadTextureFromMemory(const unsigned char* data, size_t dataLength); 

    private:
        unsigned int m_textureID, m_target;
        int m_width, m_height;
        std::string m_path, m_type, m_directory;
    };
}

#endif//OPENGL_TEXTURE_H
