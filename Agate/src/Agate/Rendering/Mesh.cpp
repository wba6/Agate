#include "Mesh.h"
#include "OpenGl/VertexArray.h"
#include "glad/glad.h"

namespace Agate {

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
    this->m_vertices = std::move(vertices);
    this->m_indices = std::move(indices);
    this->m_textures = std::move(textures);
}

//@todo we should not really render here
void Mesh::Draw(Agate::Shader &shader) {

    // Initialize texture counters
    int diffuseCount = 0;
    int specularCount = 0;
    int normalCount = 0;
    int heightCount = 0;

    shader.Bind();
    // Activate and bind each texture, assign to the shader
    for (unsigned int i = 0; i < m_textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // Activate texture unit
        m_textures[i].bind(i); // Bind texture to unit i

        std::string type = m_textures[i].getType();
        std::string name;
        if (type == "texture_diffuse") {
            name = "material.texture_diffuse[" + std::to_string(diffuseCount) + "]";
            shader.SetUniform1i(name.c_str(), i);
            diffuseCount++;
        }
        else if (type == "texture_specular") {
            name = "material.texture_specular[" + std::to_string(specularCount) + "]";
            shader.SetUniform1i(name.c_str(), i);
            specularCount++;
        }
        else if (type == "texture_normal") {
            name = "material.texture_normal[" + std::to_string(normalCount) + "]";
            shader.SetUniform1i(name.c_str(), i);
            normalCount++;
        }
        else if (type == "texture_height") {
            name = "material.texture_height[" + std::to_string(heightCount) + "]";
            shader.SetUniform1i(name.c_str(), i);
            heightCount++;
        }
    }

    // Set the counts in the shader
    shader.SetUniform1i("material.num_diffuse", diffuseCount);
    shader.SetUniform1i("material.num_specular", specularCount);
    shader.SetUniform1i("material.num_normal", normalCount);
    shader.SetUniform1i("material.num_height", heightCount);

    // Set light properties
    shader.SetUniform3f("pointLight.Color", 1.0f, 1.0f, 1.0f);           // Color: White light
    shader.SetUniform1f("pointLight.Intensity", 5.0f);                              // Intensity: Standard brightness
    shader.SetUniform1f("pointLight.Constant", 1.0f);                               // Attenuation: Constant factor
    shader.SetUniform1f("pointLight.Linear", .09f);                                // Attenuation: Linear factor
    shader.SetUniform1f("pointLight.Quadratic", 0.032f);                           // Attenuation: Quadratic factor

    //don't think this line is needed
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    m_VA->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, 0);
    m_VA->UnBind();
}

void Mesh::setupMesh() {

    if (m_vertices.empty()) {
        return;
    }

    BufferDataLayout layout{
            {"vertex positions",      vertexType::Float3},
            {"vertex normals",        vertexType::Float3},
            {"vertex texture coords", vertexType::Float2},
            {"tangent",               vertexType::Float3},
            {"BiTangent",             vertexType::Float3},
    };

    IndexBuffer IB(m_indices);

    m_VA = std::make_shared<VertexArray>(layout, m_vertices.data(), m_vertices.size() * sizeof(Vertex));
    m_VA->addIndexBuffer(IB);
}

Mesh::~Mesh() = default;

} // namespace Agate
