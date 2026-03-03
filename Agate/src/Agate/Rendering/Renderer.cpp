#include "Renderer.hpp"
#include "Rendering/OpenGl/IndexBuffer.h"
#include "Rendering/OpenGl/VertexArray.h"

namespace Agate {
    std::queue<std::unique_ptr<RenderCommand>> Renderer::s_CommandQueue;
    std::queue<std::unique_ptr<RenderCommand>> Renderer::s_ExecuteQueue;
    std::mutex Renderer::s_CommandMutex;
    // Resource Maps
    std::unordered_map<UUID, std::shared_ptr<VertexArray>> Renderer::s_VaoMap;
    std::unordered_map<UUID, std::shared_ptr<IndexBuffer>> Renderer::s_IndexBufferMap;
    std::unordered_map<UUID, Texture> Renderer::s_TextureMap;
    std::unordered_map<UUID, Shader> Renderer::s_ShaderMap;

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
    void Renderer::CreateShader(){}

    /**
     */
    void Renderer::CreateTexture(){}

}
