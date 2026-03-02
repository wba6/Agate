#include "Renderer.hpp"

namespace Agate {
    std::queue<std::unique_ptr<RenderCommand>> Renderer::s_CommandQueue;
    std::queue<std::unique_ptr<RenderCommand>> Renderer::s_ExecuteQueue;
    std::mutex Renderer::s_CommandMutex;

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

            if (e) {
                e->Execute();
            }
        }
    }
}
