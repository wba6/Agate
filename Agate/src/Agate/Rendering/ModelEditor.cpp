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

    const glm::mat4 translation{
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        m_transform.position.x, m_transform.position.y, m_transform.position.z, 1
    };
    const glm::mat4 scale{
        m_transform.scale.x, 0, 0, 0,
        0, m_transform.scale.y, 0, 0,
        0, 0, m_transform.scale.z, 0,
        0, 0, 0, 1
    };
    const glm::mat4 rotation = glm::mat4_cast(m_transform.rotation);

    return translation * rotation * scale;
}

glm::vec3 ModelEditor::EulerAngles() const {
    return glm::eulerAngles(m_transform.rotation);
}

} // namespace Agate
