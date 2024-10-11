#include "ModelLoader.h"
#include "Agate/Core/Logger.h"
#include "glad/glad.h"
#include "OpenGl/VertexArray.h"
#include <utility>
#include <filesystem>

namespace fs = std::filesystem;
glm::mat4 convertMatrix(const aiMatrix4x4 &matrix) {
    return glm::mat4(matrix.a1, matrix.b1, matrix.c1, matrix.d1,
                     matrix.a2, matrix.b2, matrix.c2, matrix.d2,
                     matrix.a3, matrix.b3, matrix.c3, matrix.d3,
                     matrix.a4, matrix.b4, matrix.c4, matrix.d4);
}
Agate::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
    this->vertices = std::move(vertices);
    this->indices = std::move(indices);
    this->textures = std::move(textures);

    setupMesh();
}

//@todo we should not really render here
void Agate::Mesh::Draw(Agate::Shader &shader) {

    // Initialize texture counters
    int diffuseCount = 0;
    int specularCount = 0;
    int normalCount = 0;
    int heightCount = 0;

    shader.Bind();
    // Activate and bind each texture, assign to the shader
    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // Activate texture unit
        textures[i].bind(i); // Bind texture to unit i

        std::string type = textures[i].getType();
        std::string name;
        if (type == "texture_diffuse") {
            name = "material.texture_diffuse[" + std::to_string(diffuseCount) + "]";
            shader.SetUniform1i(name.c_str(), i);
            diffuseCount++;
        }
        else if (type == "texture_specular") {
            name = "material.texture_specular[" + std::to_string(specularCount) + "]";
            shader.SetUniform1i(name.c_str(), i);
            specularCount++;
        }
        else if (type == "texture_normal") {
            name = "material.texture_normal[" + std::to_string(normalCount) + "]";
            shader.SetUniform1i(name.c_str(), i);
            normalCount++;
        }
        else if (type == "texture_height") {
            name = "material.texture_height[" + std::to_string(heightCount) + "]";
            shader.SetUniform1i(name.c_str(), i);
            heightCount++;
        }
    }

    // Set the counts in the shader
    shader.SetUniform1i("material.num_diffuse", diffuseCount);
    shader.SetUniform1i("material.num_specular", specularCount);
    shader.SetUniform1i("material.num_normal", normalCount);
    shader.SetUniform1i("material.num_height", heightCount);

    // Set light properties
    shader.SetUniform3f("pointLight.Color", 1.0f, 1.0f, 1.0f);           // Color: White light
    shader.SetUniform1f("pointLight.Intensity", 5.0f);                              // Intensity: Standard brightness
    shader.SetUniform1f("pointLight.Constant", 1.0f);                               // Attenuation: Constant factor
    shader.SetUniform1f("pointLight.Linear", .09f);                                // Attenuation: Linear factor
    shader.SetUniform1f("pointLight.Quadratic", 0.032f);                           // Attenuation: Quadratic factor

    //don't think this line is needed
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    VA->Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    VA->UnBind();
}

void Agate::Mesh::setupMesh() {

    BufferDataLayout layout{
            {"vertex positions",      vertexType::Float3},
            {"vertex normals",        vertexType::Float3},
            {"vertex texture coords", vertexType::Float2},
            {"tangent",               vertexType::Float3},
            {"BiTangent",             vertexType::Float3},
    };

    IndexBuffer IB(indices);

    VA = std::make_shared<VertexArray>(layout, &vertices[0], vertices.size() * sizeof(Vertex));
    VA->addIndexBuffer(IB);
}

Agate::Mesh::~Mesh() = default;

Agate::ModelLoader::ModelLoader(const std::string &path, bool gamma)
        : gammaCorrection(gamma) {
    loadModel(path);
    PRINTMSG("model loaded from path {}", path);
}

void Agate::ModelLoader::Draw(Agate::Shader &shader) {
    for (auto &mesh: meshes)
        mesh.Draw(shader);
}

void Agate::ModelLoader::loadModel(const std::string &path) {
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path,
                                             aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs |
                                             aiProcess_CalcTangentSpace);
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        PRINTERROR("ERROR::Model::loadModel Assimp Error: {}", importer.GetErrorString());
        return;
    }
    // retrieve the directory path of the filepath
    this->path = path;
    this->directory = extractDirectory(path);

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene, glm::mat4(1.0f));
}

void Agate::ModelLoader::processNode(aiNode *node, const aiScene *scene, const glm::mat4 &parentTransform) {
    glm::mat4 nodeTransform = parentTransform * convertMatrix(node->mTransformation);

    // process each mesh located at the current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene, nodeTransform));
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

std::vector<Agate::Texture> Agate::ModelLoader::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (auto &j: textures_loaded) {
            if (std::strcmp(j.getPath().data(), str.C_Str()) == 0) {
                textures.push_back(j);
                skip = true;
                break;
            }
        }
        if (!skip) {
            Texture texture(str.C_Str(), this->directory, gammaCorrection);
            texture.setType(typeName);
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }
    return std::move(textures);
}

std::string Agate::ModelLoader::extractDirectory(const std::string &path) {
    fs::path p(path);
    return p.parent_path().generic_string();
}

