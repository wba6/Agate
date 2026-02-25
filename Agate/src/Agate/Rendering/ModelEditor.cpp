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

void ModelEditor::Rotate(double radians, glm::vec3 axis) {
    PRINTWARN("Rotate() Not Yet Implemented");
}

void ModelEditor::SetRotation(double radians, glm::vec3 axis) {
    PRINTWARN("SetRotation() Not Yet Implemented");
}

void ModelEditor::Translate(glm::vec3 translation) {
    PRINTWARN("Translate() Not Yet Implemented");
}

void ModelEditor::SetPosition(glm::vec3 position) {
    PRINTWARN("SetPosition() Not Yet Implemented");
}

void ModelEditor::Scale(glm::vec3 scalar) {
    PRINTWARN("Scale() Not Yet Implemented");
}

void ModelEditor::SetScale(glm::vec3 scalar) {
    PRINTWARN("SetScale() Not Yet Implemented");
}


} // namespace Agate
