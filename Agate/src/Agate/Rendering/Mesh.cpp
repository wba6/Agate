#include "Mesh.h"
#include "OpenGl/VertexArray.h"
#include "glad/glad.h"

namespace Agate {

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
    this->vertices = std::move(vertices);
    this->indices = std::move(indices);
    this->textures = std::move(textures);

    setupMesh();
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
    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // Activate texture unit
        textures[i].bind(i); // Bind texture to unit i

        std::string type = textures[i].getType();
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
    VA->Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    VA->UnBind();
}

void Mesh::setupMesh() {

    BufferDataLayout layout{
            {"vertex positions",      vertexType::Float3},
            {"vertex normals",        vertexType::Float3},
            {"vertex texture coords", vertexType::Float2},
            {"tangent",               vertexType::Float3},
            {"BiTangent",             vertexType::Float3},
    };

    IndexBuffer IB(indices);

    VA = std::make_shared<VertexArray>(layout, &vertices[0], vertices.size() * sizeof(Vertex));
    VA->addIndexBuffer(IB);
}

Mesh::~Mesh() = default;

} // namespace Agate