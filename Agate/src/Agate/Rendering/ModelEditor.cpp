#include "ModelEditor.h"

namespace Agate {

ModelEditor::ModelEditor(std::string path, std::vector<Mesh> meshes)
    : m_path(path), m_meshes(meshes) {}

void ModelEditor::Draw(Shader& shader) {

    for (Mesh& mesh: m_meshes) {
        mesh.Draw(shader);
    }
}

} // namespace Agate
