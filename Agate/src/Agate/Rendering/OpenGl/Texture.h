//
// Created by William Aey on 7/27/2022.
//

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

namespace Agate {
    class Texture {
    public:
        Texture(const char *file, std::string &directory, int pixelFormat);

        void bind(unsigned int slot);

        void unBind();

        void setType(std::string &typeName);

        const std::string &getPath();

        const std::string &getType();

    private:
        unsigned int m_textureID;
        int m_width, m_height;
        std::string m_path, m_type;
    };
}

#endif//OPENGL_TEXTURE_H
