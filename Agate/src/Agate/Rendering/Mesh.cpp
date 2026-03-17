#include "Mesh.h"
#include "Rendering/Renderer.hpp"
#include <string>

namespace Agate {

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureUser> textures) {
    this->m_vertices = std::move(vertices);
    this->m_indices = std::move(indices);
    this->m_textures = std::move(textures);
}

//@todo we should not really render here
void Mesh::Draw(Agate::ShaderUser &shader) {

    // Initialize texture counters
    int diffuseCount = 0;
    int specularCount = 0;
    int normalCount = 0;
    int heightCount = 0;

    // Activate and bind each texture, assign to the shader
    for (unsigned int i = 0; i < m_textures.size(); i++) {
        // In a mock environment, we don't call glActiveTexture
        // Instead, we just set the uniform on the shader mock, 
        // which will communicate with the render thread.
        
        m_textures[i].bind(i); 

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

    // Example of using mock shader to set uniforms
    shader.SetUniform1i("material.num_diffuse", diffuseCount);
    shader.SetUniform1i("material.num_specular", specularCount);
    shader.SetUniform1i("material.num_normal", normalCount);
    shader.SetUniform1i("material.num_height", heightCount);

    // Set light properties
    shader.SetUniform3f("pointLight.Color", 1.0f, 1.0f, 1.0f);
    shader.SetUniform1f("pointLight.Intensity", 5.0f);
    shader.SetUniform1f("pointLight.Constant", 1.0f);
    shader.SetUniform1f("pointLight.Linear", .09f);
    shader.SetUniform1f("pointLight.Quadratic", 0.032f);

    Renderer::Submit(std::make_unique<DrawMesh>(m_VA->getUUID(), shader.getUUID(), static_cast<uint32_t>(m_indices.size())));
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

    // Copy data to a shared_ptr for thread safety
    size_t dataSize = m_vertices.size() * sizeof(Vertex);
    void* buffer = malloc(dataSize);
    memcpy(buffer, m_vertices.data(), dataSize);
    auto safe_data_ptr = std::shared_ptr<void>(buffer, free);

    m_VA = std::make_shared<VertexArrayUser>(layout, safe_data_ptr, dataSize);
    
    // Create IndexBufferUser which will submit CreateIndexBuffer command
    // We don't need to keep it around if the VAO creation on render thread handles it
    IndexBufferUser IB(m_indices, m_VA->getUUID());
}

Mesh::~Mesh() = default;

} // namespace Agate
