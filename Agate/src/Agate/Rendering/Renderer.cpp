#include "Renderer.hpp"

namespace Agate {
    std::queue<std::unique_ptr<RenderCommand>> Renderer::s_CommandQueue;
    void Renderer::Submit(std::unique_ptr<RenderCommand> e) {
        s_CommandQueue.push(std::move(e));
    };
    void Renderer::Flush() {
        while (!s_CommandQueue.empty()) {
            std::unique_ptr<RenderCommand> e = std::move(s_CommandQueue.front());
            s_CommandQueue.pop();

            if (e) {
                e->Execute();
            }
        }
    };
}
