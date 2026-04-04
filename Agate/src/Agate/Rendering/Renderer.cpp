#include "Renderer.hpp"
#include <glad/glad.h>
#include "Rendering/OpenGl/IndexBuffer.h"
#include "Rendering/OpenGl/VertexArray.h"
#include "Rendering/OpenGl/Shader.h"
#include "Rendering/OpenGl/Texture.h"
#include "Agate/Core/Exceptions.h"

namespace Agate {
    std::queue<std::unique_ptr<RenderCommand>> Renderer::s_CommandQueue;
    std::queue<std::unique_ptr<RenderCommand>> Renderer::s_ExecuteQueue;
    std::mutex Renderer::s_CommandMutex;
    // Resource Maps
    std::unordered_map<UUID, std::shared_ptr<VertexArray>> Renderer::s_VaoMap;
    std::unordered_map<UUID, std::shared_ptr<IndexBuffer>> Renderer::s_IndexBufferMap;
    std::unordered_map<UUID, std::shared_ptr<Texture>> Renderer::s_TextureMap;
    std::unordered_map<UUID, std::shared_ptr<Shader>> Renderer::s_ShaderMap;
    std::exception_ptr Renderer::s_RenderException = nullptr;

    void Renderer::Submit(std::unique_ptr<RenderCommand> e) {
        std::lock_guard<std::mutex> lock(s_CommandMutex);
        s_CommandQueue.push(std::move(e));
    }

    void Renderer::CheckForExceptions() {
        if (s_RenderException) {
            std::exception_ptr ex = s_RenderException;
            s_RenderException = nullptr;
            std::rethrow_exception(ex);
        }
    }

    void Renderer::Flush() {
        {
            // Lock the mutex only while swapping
            std::lock_guard<std::mutex> lock(s_CommandMutex);
            s_CommandQueue.swap(s_ExecuteQueue);
        } // Mutex is released 

        try {
            // Execute commands from the execute buffer 
            while (!s_ExecuteQueue.empty()) {
                std::unique_ptr<RenderCommand> e = std::move(s_ExecuteQueue.front());
                s_ExecuteQueue.pop();

                CommandNotifier notifier(*e);
                notifier.NotifyCommand<CreateVertexArray>(BindStaticFn(Renderer::OnCreateVAO));
                notifier.NotifyCommand<CreateIndexBuffer>(BindStaticFn(Renderer::OnCreateIB));
                notifier.NotifyCommand<CreateShader>(BindStaticFn(Renderer::OnCreateShader));
                notifier.NotifyCommand<CreateTexture>(BindStaticFn(Renderer::OnCreateTexture));
                notifier.NotifyCommand<BindVertexArray>(BindStaticFn(Renderer::OnBindVAO));
                notifier.NotifyCommand<UnBindVertexArray>(BindStaticFn(Renderer::OnUnBindVAO));
                notifier.NotifyCommand<BindIndexBuffer>(BindStaticFn(Renderer::OnBindIBO));
                notifier.NotifyCommand<UnBindIndexBuffer>(BindStaticFn(Renderer::OnUnBindIBO));
                notifier.NotifyCommand<BindShader>(BindStaticFn(Renderer::OnBindShader));
                notifier.NotifyCommand<UnBindShader>(BindStaticFn(Renderer::OnUnBindShader));
                notifier.NotifyCommand<BindTexture>(BindStaticFn(Renderer::OnBindTexture));
                notifier.NotifyCommand<DrawMesh>(BindStaticFn(Renderer::OnDrawMesh));
                notifier.NotifyCommand<UpdateShaderUniform4f>(BindStaticFn(Renderer::OnUpdateShaderUniform4f));
                notifier.NotifyCommand<UpdateShaderUniform3f>(BindStaticFn(Renderer::OnUpdateShaderUniform3f));
                notifier.NotifyCommand<UpdateShaderUniformMat4>(BindStaticFn(Renderer::OnUpdateShaderUniformMat4));
                notifier.NotifyCommand<UpdateShaderUniform1i>(BindStaticFn(Renderer::OnUpdateShaderUniform1i));
                notifier.NotifyCommand<UpdateShaderUniform1f>(BindStaticFn(Renderer::OnUpdateShaderUniform1f));
                notifier.NotifyCommand<SetViewport>(BindStaticFn(Renderer::OnSetViewport));
                notifier.NotifyCommand<DeleteVertexArray>(BindStaticFn(Renderer::OnDeleteVAO));
                notifier.NotifyCommand<DeleteIndexBuffer>(BindStaticFn(Renderer::OnDeleteIBO));
                notifier.NotifyCommand<DeleteShader>(BindStaticFn(Renderer::OnDeleteShader));
                notifier.NotifyCommand<DeleteTexture>(BindStaticFn(Renderer::OnDeleteTexture));


                if (e) {
                    e->Execute();
                }
            }
        } catch (...) {
            s_RenderException = std::current_exception();
            // clear the queue to stop rendering on error
            while (!s_ExecuteQueue.empty()) s_ExecuteQueue.pop();
        }
    }

     /**
     */
    void Renderer::OnCreateVAO(CreateVertexArray e) {
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
    void Renderer::OnCreateIB(CreateIndexBuffer e) {
        auto vaoIterator = s_VaoMap.find(e.m_VAUUID);
        if (vaoIterator == s_VaoMap.end()) {
            throw UUIDNotFoundException(e.m_VAUUID, "VertexArray");
        }

        // Allocate the IndexBuffer as a shared_ptr
        auto ib = std::make_shared<IndexBuffer>(e.m_IBU.getIndinces());

        vaoIterator->second->addIndexBuffer(*ib);

        // Store the exact same shared pointer in your Index Buffer map
        s_IndexBufferMap[e.m_IBU.getUUID()] = ib;
    }

    /**
     */
    void Renderer::OnCreateShader(CreateShader e){
        auto shader = std::make_shared<Shader>(
            e.m_SU.getVertexShaderPath().c_str(), 
            e.m_SU.getFragmentShaderPath().c_str()
        );
        s_ShaderMap[e.m_SU.getUUID()] = shader;
    }

    /**
     */
    void Renderer::OnCreateTexture(CreateTexture e){
        auto texture = std::make_shared<Texture>(
            e.m_TU.getPath().c_str(),
            e.m_TU.getDirectory()
        );
        texture->initialize();
        s_TextureMap[e.m_TU.getUUID()] = texture;
    }

    void Renderer::OnBindVAO(BindVertexArray e) {
        auto it = s_VaoMap.find(e.m_UUID);
        if (it == s_VaoMap.end()) {
            throw UUIDNotFoundException(e.m_UUID, "VertexArray");
        }
        it->second->Bind();
    }

    void Renderer::OnUnBindVAO(UnBindVertexArray e) {
        // We don't need a specific VAO to unbind in OpenGL
        glBindVertexArray(0);
    }

    void Renderer::OnBindIBO(BindIndexBuffer e) {
        auto it = s_IndexBufferMap.find(e.m_UUID);
        if (it == s_IndexBufferMap.end()) {
            throw UUIDNotFoundException(e.m_UUID, "IndexBuffer");
        }
        it->second->Bind();
    }

    void Renderer::OnUnBindIBO(UnBindIndexBuffer e) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Renderer::OnBindShader(BindShader e) {
        auto it = s_ShaderMap.find(e.m_UUID);
        if (it == s_ShaderMap.end()) {
            throw UUIDNotFoundException(e.m_UUID, "Shader");
        }
        it->second->Bind();
    }

    void Renderer::OnUnBindShader(UnBindShader e) {
        glUseProgram(0);
    }

    void Renderer::OnBindTexture(BindTexture e) {
        auto it = s_TextureMap.find(e.m_UUID);
        if (it == s_TextureMap.end()) {
            throw UUIDNotFoundException(e.m_UUID, "Texture");
        }
        it->second->bind(e.m_Slot);
    }

    void Renderer::OnDrawMesh(DrawMesh e) {
        auto vaoIt = s_VaoMap.find(e.m_VaoUUID);
        if (vaoIt == s_VaoMap.end()) {
            throw UUIDNotFoundException(e.m_VaoUUID, "VertexArray");
        }
        auto shaderIt = s_ShaderMap.find(e.m_ShaderUUID);
        if (shaderIt == s_ShaderMap.end()) {
            throw UUIDNotFoundException(e.m_ShaderUUID, "Shader");
        }

        shaderIt->second->Bind();
        vaoIt->second->Bind();
        glDrawElements(GL_TRIANGLES, e.m_IndexCount, GL_UNSIGNED_INT, 0);
        vaoIt->second->UnBind();
    }

    void Renderer::OnUpdateShaderUniform4f(UpdateShaderUniform4f e) {
        auto shaderIt = s_ShaderMap.find(e.m_ShaderUUID);
        if (shaderIt == s_ShaderMap.end()) {
            throw UUIDNotFoundException(e.m_ShaderUUID, "Shader");
        }
        shaderIt->second->Bind();
        shaderIt->second->SetUniform4f(e.m_Uniform.c_str(), e.m_X, e.m_Y, e.m_Z, e.m_W);
    }

    void Renderer::OnUpdateShaderUniform3f(UpdateShaderUniform3f e) {
        auto shaderIt = s_ShaderMap.find(e.m_ShaderUUID);
        if (shaderIt == s_ShaderMap.end()) {
            throw UUIDNotFoundException(e.m_ShaderUUID, "Shader");
        }
        shaderIt->second->Bind();
        shaderIt->second->SetUniform3f(e.m_Uniform.c_str(), e.m_X, e.m_Y, e.m_Z);
    }

    void Renderer::OnUpdateShaderUniformMat4(UpdateShaderUniformMat4 e) {
        auto shaderIt = s_ShaderMap.find(e.m_ShaderUUID);
        if (shaderIt == s_ShaderMap.end()) {
            throw UUIDNotFoundException(e.m_ShaderUUID, "Shader");
        }
        shaderIt->second->Bind();
        shaderIt->second->SetUniformMat4(e.m_Uniform.c_str(), e.m_Trans);
    }

    void Renderer::OnUpdateShaderUniform1i(UpdateShaderUniform1i e) {
        auto shaderIt = s_ShaderMap.find(e.m_ShaderUUID);
        if (shaderIt == s_ShaderMap.end()) {
            throw UUIDNotFoundException(e.m_ShaderUUID, "Shader");
        }
        shaderIt->second->Bind();
        shaderIt->second->SetUniform1i(e.m_Uniform.c_str(), e.m_Value);
    }

    void Renderer::OnUpdateShaderUniform1f(UpdateShaderUniform1f e) {
        auto shaderIt = s_ShaderMap.find(e.m_ShaderUUID);
        if (shaderIt == s_ShaderMap.end()) {
            throw UUIDNotFoundException(e.m_ShaderUUID, "Shader");
        }
        shaderIt->second->Bind();
        shaderIt->second->SetUniform1f(e.m_Uniform.c_str(), e.m_X);
    }

    void Renderer::OnSetViewport(SetViewport e) {
        glViewport(e.m_X, e.m_Y, e.m_Width, e.m_Height);
    }

    void Renderer::OnDeleteVAO(DeleteVertexArray e) {
        s_VaoMap.erase(e.m_UUID);
    }

    void Renderer::OnDeleteIBO(DeleteIndexBuffer e) {
        s_IndexBufferMap.erase(e.m_UUID);
    }

    void Renderer::OnDeleteShader(DeleteShader e) {
        s_ShaderMap.erase(e.m_UUID);
    }

    void Renderer::OnDeleteTexture(DeleteTexture e) {
        s_TextureMap.erase(e.m_UUID);
    }

}
