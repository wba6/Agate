#include "ModelEditor.h"
#include <glm/glm.hpp>

namespace Agate {

Transform::Transform()
        : position(glm::vec3(0, 0, 0)),
          scale(glm::vec3(1, 1, 1)),
          rotation(glm::quat(0, 1, 0, 0))  {}

ModelEditor::ModelEditor(std::string path, std::vector<Mesh> meshes)
        : m_path(path), m_meshes(meshes) {}

void ModelEditor::Draw(Shader& shader) {

    for (Mesh& mesh: m_meshes) {
        mesh.Draw(shader);
    }
}

void ModelEditor::Rotate(glm::f32 radians, const glm::vec3& axis) {
    m_transform.rotation = glm::angleAxis(radians, axis) * m_transform.rotation;
}

void ModelEditor::SetRotation(glm::f32 radians, const glm::vec3& axis) {
    m_transform.rotation = glm::angleAxis(radians, axis);
}

void ModelEditor::Translate(const glm::vec3& translation) {
    m_transform.position += translation;
}

void ModelEditor::SetPosition(const glm::vec3& position) {
    m_transform.position = position;
}

void ModelEditor::Scale(const glm::vec3& scalar) {
    m_transform.scale *= scalar;
}

void ModelEditor::SetScale(const glm::vec3& scalar) {
    m_transform.scale = scalar;
}

glm::mat4 ModelEditor::ModelMatrix() const {

    glm::mat4 model{ 1.0f };
    const glm::mat4 translation = glm::translate(model, m_transform.position);
    model = model * glm::mat4_cast(m_transform.rotation);

    return glm::scale(model, m_transform.scale);
}

glm::vec3 ModelEditor::EulerAngles() const {
    return glm::eulerAngles(m_transform.rotation);
}

void ModelEditor::LoadTextures() {

    /*
        This seems to block for quite a while after the model
        loads, but I think a fix should be deferred until this
        is running on the render thread
    */
    PRINTMSG("Loading textures - This may take a minute");
    for (auto& mesh: m_meshes) {
        for (auto& texture: mesh.m_textures) {
            texture.initialize();
        }
        mesh.setupMesh();
    }
}

} // namespace Agate
