#include <memory.h>
#include <queue>
#include "OpenGL/Shader.h"
#include "Rendering/OpenGl/VertexArray.h"

#ifndef RENDERCOMMAND_HPP
#define RENDERCOMMAND_HPP

namespace Agate {
    struct RenderCommand {
        // These types will need to be expanded
        enum Type { DrawIndex, DrawMesh, SetViewport } type;

        std::shared_ptr<Shader> m_shader;
        std::shared_ptr<VertexArray> m_vao;
        // ... other rendering state data

    };

    class Renderer {
        public:
            static void Submit(const RenderCommand& cmd);
            static void Flush();
        private:
            std::queue<RenderCommand> s_CommandQueue;
    };
}
#endif // RENDERCOMMAND_HPP
