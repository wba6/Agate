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

Agate::TaskHandle<Agate::ModelEditor> Agate::ModelLoader::LoadModel(const std::string &path, bool flipUVs) {

    return Agate::TaskPool::Enqueue([path, flipUVs]() -> Agate::ModelEditor {
        
        std::unique_ptr<Agate::ModelLoader> loader = std::make_unique<Agate::AssimpLoader>(path, flipUVs);
        if (!loader->loadModel()) {
            throw std::runtime_error(fmt::format("Failed to load model from {}", path));
        }
        loader->m_meshes = loader->parseModel();

        return Agate::ModelEditor(std::move(loader->m_path), std::move(loader->m_meshes));
    });
}

std::string Agate::ModelLoader::extractDirectory(const std::string &path) {
    fs::path p(path);
    return p.parent_path().generic_string();
}
