#include "agpch.h"
#include "ModelLoader.h"
#include "AssimpLoader.h"
#include "Mesh.h"
#include "ModelEditor.h"
#include <utility>
#include <memory>

namespace fs = std::filesystem;

Agate::ModelLoader::~ModelLoader() = default;

Agate::ModelLoader::ModelLoader(std::string const &path)
    : m_directory(extractDirectory(path)), m_path(path) {}

void Agate::ModelLoader::Draw(Agate::Shader &shader) {
    m_model.Draw(shader);
}

std::future<std::unique_ptr<Agate::ModelLoader>> Agate::ModelLoader::LoadModel(const std::string &path) {

    return std::async(std::launch::async, [path]() {

        std::unique_ptr<Agate::ModelLoader> loader = std::make_unique<AssimpLoader>(path);
        loader->loadModel();
        loader->m_meshes = loader->parseModel();
        loader->m_model = Agate::ModelEditor(loader->m_path, loader->m_meshes);

        return loader;
    });
}

std::string Agate::ModelLoader::extractDirectory(const std::string &path) {
    fs::path p(path);
    return p.parent_path().generic_string();
}
