#include "Renderer.hpp"
#include "Rendering/OpenGl/IndexBuffer.h"
#include "Rendering/OpenGl/VertexArray.h"
#include "Rendering/OpenGl/Shader.h"
#include "Rendering/OpenGl/Texture.h"

namespace Agate {
    std::queue<std::unique_ptr<RenderCommand>> Renderer::s_CommandQueue;
    std::queue<std::unique_ptr<RenderCommand>> Renderer::s_ExecuteQueue;
    std::mutex Renderer::s_CommandMutex;
    // Resource Maps
    std::unordered_map<UUID, std::shared_ptr<VertexArray>> Renderer::s_VaoMap;
    std::unordered_map<UUID, std::shared_ptr<IndexBuffer>> Renderer::s_IndexBufferMap;
    std::unordered_map<UUID, std::shared_ptr<Texture>> Renderer::s_TextureMap;
    std::unordered_map<UUID, std::shared_ptr<Shader>> Renderer::s_ShaderMap;

    void Renderer::Submit(std::unique_ptr<RenderCommand> e) {
        std::lock_guard<std::mutex> lock(s_CommandMutex);
        s_CommandQueue.push(std::move(e));
    }

    void Renderer::Flush() {
        {
            // Lock the mutex only while swapping
            std::lock_guard<std::mutex> lock(s_CommandMutex);
            s_CommandQueue.swap(s_ExecuteQueue);
        } // Mutex is released 

        // Execute commands from the execute buffer 
        while (!s_ExecuteQueue.empty()) {
            std::unique_ptr<RenderCommand> e = std::move(s_ExecuteQueue.front());
            s_ExecuteQueue.pop();

            CommandNotifier notifier(*e);
            notifier.NotifyCommand<CreateVertexArray>(BindStaticFn(Renderer::CreateVAO));
            notifier.NotifyCommand<CreateIndexBuffer>(BindStaticFn(Renderer::CreateIB));
            notifier.NotifyCommand<CreateShader>(BindStaticFn(Renderer::CreateShader));
            notifier.NotifyCommand<CreateTexture>(BindStaticFn(Renderer::CreateTexture));
            notifier.NotifyCommand<UpdateShaderUniform4f>(BindStaticFn(Renderer::UpdateShaderUniform4f));
            notifier.NotifyCommand<UpdateShaderUniform3f>(BindStaticFn(Renderer::UpdateShaderUniform3f));
            notifier.NotifyCommand<UpdateShaderUniformMat4>(BindStaticFn(Renderer::UpdateShaderUniformMat4));
            notifier.NotifyCommand<UpdateShaderUniform1i>(BindStaticFn(Renderer::UpdateShaderUniform1i));
            notifier.NotifyCommand<UpdateShaderUniform1f>(BindStaticFn(Renderer::UpdateShaderUniform1f));


            if (e) {
                e->Execute();
            }
        }
    }

     /**
     */
    void Renderer::CreateVAO(CreateVertexArray e) {
        // We removed the old "not smart" comment because it's smart now!
        // Allocate the VertexArray on the heap and wrap it in a shared_ptr
        auto vao = std::make_shared<VertexArray>(
            e.m_VAU.getBufferData(), 
            e.m_VAU.getData().get(), 
            e.m_VAU.getDataSize()
        );
        
        s_VaoMap[e.m_VAU.getUUID()] = vao;
    }

    /**
     */
    void Renderer::CreateIB(CreateIndexBuffer e) {
        // Safely look up the VAO using .find() to prevent default-construction
        auto vaoIterator = s_VaoMap.find(e.m_VAUUID);
        if (vaoIterator == s_VaoMap.end()) {
            // ERROR: The VAO doesn't exist 
            return; 
        }

        // Allocate the IndexBuffer as a shared_ptr
        auto ib = std::make_shared<IndexBuffer>(e.m_IBU.getIndinces());

        // Add the shared pointer to the VAO safely
        vaoIterator->second->addIndexBuffer(*ib);

        // Store the exact same shared pointer in your Index Buffer map
        s_IndexBufferMap[e.m_IBU.getUUID()] = ib;
    }

    /**
     */
    void Renderer::CreateShader(CreateShader e){
        auto shader = std::make_shared<Shader>(
            e.m_SU.getVertexShaderPath().c_str(), 
            e.m_SU.getFragmentShaderPath().c_str()
        );
        s_ShaderMap[e.m_SU.getUUID()] = shader;
    }

    /**
     */
    void Renderer::CreateTexture(CreateTexture e){
        auto texture = std::make_shared<Texture>(
            e.m_TU.getPath().c_str(),
            e.m_TU.getDirectory()
        );
        texture->initialize();
        s_TextureMap[e.m_TU.getUUID()] = texture;
    }

    void Renderer::UpdateShaderUniform4f(UpdateShaderUniform4f e) {
        auto shaderIt = s_ShaderMap.find(e.m_ShaderUUID);
        if (shaderIt != s_ShaderMap.end()) {
            shaderIt->second->Bind();
            shaderIt->second->SetUniform4f(e.m_Uniform.c_str(), e.m_X, e.m_Y, e.m_Z, e.m_W);
        }
    }

    void Renderer::UpdateShaderUniform3f(UpdateShaderUniform3f e) {
        auto shaderIt = s_ShaderMap.find(e.m_ShaderUUID);
        if (shaderIt != s_ShaderMap.end()) {
            shaderIt->second->Bind();
            shaderIt->second->SetUniform3f(e.m_Uniform.c_str(), e.m_X, e.m_Y, e.m_Z);
        }
    }

    void Renderer::UpdateShaderUniformMat4(UpdateShaderUniformMat4 e) {
        auto shaderIt = s_ShaderMap.find(e.m_ShaderUUID);
        if (shaderIt != s_ShaderMap.end()) {
            shaderIt->second->Bind();
            shaderIt->second->SetUniformMat4(e.m_Uniform.c_str(), e.m_Trans);
        }
    }

    void Renderer::UpdateShaderUniform1i(UpdateShaderUniform1i e) {
        auto shaderIt = s_ShaderMap.find(e.m_ShaderUUID);
        if (shaderIt != s_ShaderMap.end()) {
            shaderIt->second->Bind();
            shaderIt->second->SetUniform1i(e.m_Uniform.c_str(), e.m_Value);
        }
    }

    void Renderer::UpdateShaderUniform1f(UpdateShaderUniform1f e) {
        auto shaderIt = s_ShaderMap.find(e.m_ShaderUUID);
        if (shaderIt != s_ShaderMap.end()) {
            shaderIt->second->Bind();
            shaderIt->second->SetUniform1f(e.m_Uniform.c_str(), e.m_X);
        }
    }

}
