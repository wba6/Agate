#ifndef AGATE_MODELLOADER_H
#define AGATE_MODELLOADER_H

#include "agpch.h"
#include "glm/glm.hpp"
#include "OpenGl/Shader.h"

namespace Agate {
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };

    struct Texture {
        unsigned int id;
        std::string type;
    };

    class Mesh {
    public:
        // mesh data
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

        void Draw(Shader &shader);

    private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void setupMesh();
    };

    class modelLoader {

    };

}

#endif //AGATE_MODELLOADER_H
