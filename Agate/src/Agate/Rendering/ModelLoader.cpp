#include "agpch.h"
#include "ModelLoader.h"
#include "Mesh.h"
#include <utility>

namespace fs = std::filesystem;

Agate::ModelLoader::ModelLoader(std::string const &path)
    : m_directory(extractDirectory(path)), m_path(path) {}

void Agate::ModelLoader::Draw(Agate::Shader &shader) {

    // Once we get the scene we prepare it, i.e once we get the futures value we use it 
    // once used it is no longer valid i.e this if is skipped
    if (m_futureScene.valid()) {
        auto status = m_futureScene.wait_for(std::chrono::seconds(0));
        if (status == std::future_status::ready) {
            // Once this is done the future scene will no longer be valid
            m_futureScene.get();
            m_meshes = parseModel();
        }
    }

    for (auto &mesh: m_meshes)
        mesh.Draw(shader);
}

void Agate::ModelLoader::LoadModel() {
    m_futureScene = loadModel();
}

std::string Agate::ModelLoader::extractDirectory(const std::string &path) {
    fs::path p(path);
    return p.parent_path().generic_string();
}
