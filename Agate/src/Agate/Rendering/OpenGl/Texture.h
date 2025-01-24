//
// Created by William Aey on 7/27/2022.
//

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

namespace Agate {
    class Texture {
    public:
        Texture(const char *file, std::string &directory, int pixelFormat);

        void bind(unsigned int slot) const;

        void unBind() const;

        void setType(std::string &typeName);

        const std::string &getPath();

        const std::string &getType();

    private:
        bool load_standard_texture_with_soil2(const std::string& filename, unsigned int& textureID, unsigned int& target, int& width, int& height);
        bool load_ktx_with_libktx(const std::string& filename, unsigned int& textureID, unsigned int& target, int& width, int& height);

    private:
        unsigned int m_textureID, m_target;
        int m_width, m_height;
        std::string m_path, m_type;
    };
}

#endif//OPENGL_TEXTURE_H
