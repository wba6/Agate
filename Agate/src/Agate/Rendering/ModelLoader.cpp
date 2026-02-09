#include "agpch.h"
#include "ModelLoader.h"
#include "Agate/Core/Logger.h"
#include "Mesh.h"
#include "assimp/scene.h"
#include "glad/glad.h"
#include <utility>

namespace fs = std::filesystem;

/*
 * Convert an assimp matrix to a glm matrix, this is the best way I can find to do this
 *
 * @param matrix The assimp matrix to convert
 * @return The converted glm matrix
 */
inline glm::mat4 convertMatrix(const aiMatrix4x4 &matrix) {
    return glm::mat4(matrix.a1, matrix.b1, matrix.c1, matrix.d1,
                     matrix.a2, matrix.b2, matrix.c2, matrix.d2,
                     matrix.a3, matrix.b3, matrix.c3, matrix.d3,
                     matrix.a4, matrix.b4, matrix.c4, matrix.d4);
}

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
            processNode(scene->mRootNode, scene, glm::mat4(1.0f));
            PRINTMSG("Model loaded from path: {}", m_path);
}

void Agate::ModelLoader::processNode(aiNode *node, const aiScene *scene, const glm::mat4 &parentTransform) {
    glm::mat4 nodeTransform = parentTransform * convertMatrix(node->mTransformation);

    // process each mesh located at the current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(assimp.processMesh(mesh, scene, nodeTransform, textures_loaded));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, nodeTransform);
    }
}

std::string Agate::ModelLoader::extractDirectory(const std::string &path) {
    fs::path p(path);
    return p.parent_path().generic_string();
}
