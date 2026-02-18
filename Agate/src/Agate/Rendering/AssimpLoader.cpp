#include "AssimpLoader.h"
#include "Agate/Core/Logger.h"
#include "Mesh.h"
#include "OpenGl/Texture.h"
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <future>
#include <string>

namespace {

/**
 * Convert an assimp matrix to a glm matrix
 *
 * @param matrix The assimp matrix to convert
 * @return Converted glm matrix
 */
inline glm::mat4 convertMatrix(const aiMatrix4x4& matrix) {
    return glm::mat4(matrix.a1, matrix.b1, matrix.c1, matrix.d1,
                     matrix.a2, matrix.b2, matrix.c2, matrix.d2,
                     matrix.a3, matrix.b3, matrix.c3, matrix.d3,
                     matrix.a4, matrix.b4, matrix.c4, matrix.d4);
}

} // anonymous namespace

namespace Agate {

AssimpLoader::AssimpLoader(std::string path, bool flipUVs):
        ModelLoader(path), m_flipUVs(flipUVs), m_scene(nullptr) {}

std::future<bool> AssimpLoader::loadModel() {

    unsigned int flags = getFlags();

    return std::async(std::launch::async, [this, flags]() {

        this->m_scene = m_importer.ReadFile(this->m_path, flags);

        if (!m_scene || m_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_scene->mRootNode) {
            PRINTERROR("ASSIMP ERROR: {}", m_importer.GetErrorString());
            return false;
        }

        return true;
    });
}

std::vector<Mesh> AssimpLoader::parseModel() {

    if (!m_scene) {
        PRINTERROR("No scene to prepare");
        return std::vector<Mesh>();
    }

    std::vector<Mesh> nodeMeshes = processNode(m_scene->mRootNode, m_scene, glm::mat4(1.0f));
    PRINTMSG("Model loaded from path \"{}\" with {} meshes", m_path, nodeMeshes.size());

    return nodeMeshes;
}

std::vector<Mesh> Agate::AssimpLoader::processNode(aiNode *node, const aiScene *scene, const glm::mat4 &parentTransform) {

    glm::mat4 nodeTransform = parentTransform * convertMatrix(node->mTransformation);
    std::vector<Mesh> meshes;

    // Parse meshes in current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene, nodeTransform));
    }

    // Process child nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        std::vector<Mesh> childMeshes = processNode(node->mChildren[i], scene, nodeTransform);
        meshes.insert(meshes.end(), childMeshes.begin(), childMeshes.end());
    }

    return meshes;
}

Mesh AssimpLoader::processMesh(aiMesh *mesh, const aiScene *scene, const glm::mat4 &transform) {
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

    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return Mesh{vertices, indices, textures};
}

std::vector<Texture> AssimpLoader::loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName) {

    std::vector<Texture> textures;
    for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
        aiString str;
        material->GetTexture(type, i, &str);
        bool skip = false;
        for (auto &j: m_texturesLoaded) {
            if (std::strcmp(j.getPath().data(), str.C_Str()) == 0) {
                textures.push_back(j);
                skip = true;
                break;
            }
        }
        if (!skip) {
            Texture texture(str.C_Str(), m_directory);
            texture.setType(typeName);
            textures.push_back(texture);
            m_texturesLoaded.push_back(texture);
        }
    }
    return textures;
}

unsigned int AssimpLoader::getFlags() const {

    // default flags
    unsigned int assimpFlags = aiProcess_CalcTangentSpace     |
                            aiProcess_Triangulate             |
                            aiProcess_JoinIdenticalVertices   |
                            aiProcess_SortByPType;

    // option flipUVs
    if(m_flipUVs) {
        assimpFlags |= aiProcess_FlipUVs;
    }

    return assimpFlags;
}

} // namespace Agate
