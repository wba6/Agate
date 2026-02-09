#include "agpch.h"
#include "ModelLoader.h"
#include "Agate/Core/Logger.h"
#include "Mesh.h"
#include "assimp/scene.h"
#include "glad/glad.h"
#include <utility>

namespace fs = std::filesystem;

Agate::ModelLoader::ModelLoader(std::string const &path, bool flipUVs)
    : m_directory(extractDirectory(path)), m_path(path), assimp(extractDirectory(path)) {
    // read file via ASSIMP
    unsigned int assimpFlags = assimp.getFlags(flipUVs);

    // This future is used to async load the data of the model file
    m_futureScene = assimp.readFile(m_path, assimpFlags); 

}

void Agate::ModelLoader::Draw(Agate::Shader &shader) {

    // Once we get the scene we prepare it, i.e once we get the futures value we use it 
    // once used it is no longer valid i.e this if is skipped
    if (m_futureScene.valid()) {
        auto status = m_futureScene.wait_for(std::chrono::seconds(0));
        if (status == std::future_status::ready) {
            // Once this is done the future scene will no longer be valid
            prepareScene(m_futureScene.get());
        }
    }

    for (auto &mesh: m_meshes)
        mesh.Draw(shader);
}

void Agate::ModelLoader::prepareScene(const aiScene *scene) {
            // Is the scene valid?
            if (!scene) {
                PRINTERROR("No scene to prepare");
                return;
            }

            // Proccess the nodes once (Note this can be very expensive)
            std::vector<Mesh> nodeMeshes = assimp.processNode(scene->mRootNode, scene, glm::mat4(1.0f), textures_loaded);
            m_meshes.insert(m_meshes.end(), nodeMeshes.begin(), nodeMeshes.end());
            PRINTMSG("Model loaded from path: {}", m_path);
}

std::string Agate::ModelLoader::extractDirectory(const std::string &path) {
    fs::path p(path);
    return p.parent_path().generic_string();
}
