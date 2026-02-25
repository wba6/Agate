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

} // namespace Agate
