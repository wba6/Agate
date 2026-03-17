/**
 * @brief Include file for the Mesh class
 * 
 * Has render data for OpenGL and the ability to invoke OpenGL
 * to draw itself
 */

#ifndef AGATE_MESH_H
#define AGATE_MESH_H

#include "mock/ShaderUser.hpp"
#include "mock/TextureUser.hpp"
#include "mock/VertexArrayUser.hpp"
#include "mock/IndexBufferUser.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace Agate {

/**
 * @brief A vertex with a position, normal, texture coordinate,
 *        tangent, and bitangent
 */
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

class Mesh {
public:

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<TextureUser> m_textures;

    /**
     * @brief Constructor from mesh data
     * 
     * @param vertices Vertices that make up the mesh
     * @param indices Relative indices of the mesh vertices to map to faces
     * @param textures Textures required by this mesh
     */
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureUser> textures);

    /**
     * @brief Draws this mesh
     * 
     * @param shader Shader to bind and use for shading the mesh
     */
    void Draw(ShaderUser &shader);

    virtual ~Mesh();

    void setupMesh();

private:
    //  render data
    std::shared_ptr<VertexArrayUser> m_VA;


};

}

#endif // AGATE_MESH_H
