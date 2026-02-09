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
        m_meshes.push_back(processMesh(mesh, scene, nodeTransform));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, nodeTransform);
    }
}

Agate::Mesh Agate::ModelLoader::processMesh(aiMesh *mesh, const aiScene *scene, const glm::mat4 &transform) {
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vector;
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = glm::vec3(transform * glm::vec4(vector, 1.0f));
        // normals
        if (mesh->HasNormals()) {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = glm::mat3(transform) * vector;
        }
        // texture coordinates
        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = glm::mat3(transform) * vector;
            // bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = glm::mat3(transform) * vector;
        } else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }
    // now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<Texture> diffuseMaps = assimp.loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", textures_loaded);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<Texture> specularMaps = assimp.loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", textures_loaded);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector<Texture> normalMaps = assimp.loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal", textures_loaded);
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<Texture> heightMaps = assimp.loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height", textures_loaded);
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return Mesh{vertices, indices, textures};
}

std::string Agate::ModelLoader::extractDirectory(const std::string &path) {
    fs::path p(path);
    return p.parent_path().generic_string();
}
