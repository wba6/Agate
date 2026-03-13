
#ifndef AGATE_RENDERER_HPP
#define AGATE_RENDERER_HPP

#include <memory.h>
#include <queue>
#include <unordered_map>
#include "Event.h"
#include "RenderCommand.hpp"
#include "Rendering/OpenGl/IndexBuffer.h"
#include "Rendering/OpenGl/Texture.h"
#include "Rendering/OpenGl/VertexArray.h"
#include "Rendering/OpenGl/Shader.h"

namespace Agate {

    /**
     * @brief Centralized render command dispatcher.
     *
     * Renderer provides a simple, static interface for queuing render commands
     *
     * Typical usage is:
     * - Call @ref Submit to enqueue commands during update/game logic.
     * - Call @ref Flush once per frame (or at a defined sync point) to execute all queued commands.
     *
     * Ownership of commands is transferred to the renderer via @c std::unique_ptr,
     * ensuring commands are cleaned up automatically after execution and removal from the queue.
     */
    class Renderer {
        public:

            /**
             * @brief Enqueue a render command for later execution.
             *
             * Takes ownership of the provided command and stores it in the internal queue.
             * The command will be executed the next time @ref Flush is called.
             *
             * @param e Render command to enqueue. Ownership is moved into the renderer.
             */
            static void Submit(std::unique_ptr<RenderCommand> e);

            /**
             * @brief Execute all queued render commands.
             *
             * Iterates through the internal command queue, executing each stored command
             * (typically issuing OpenGL calls), and empties the queue.
             */
            static void Flush();

            /**
             */
            static void CreateVAO(CreateVertexArray e);

            /**
             */
            static void CreateIB(CreateIndexBuffer e);

            
            /**
             */
            static void CreateShader(CreateShader e);

            /**
             */
            static void CreateTexture(CreateTexture e);

            static void UpdateShaderUniform4f(UpdateShaderUniform4f e);
            static void UpdateShaderUniform3f(UpdateShaderUniform3f e);
            static void UpdateShaderUniformMat4(UpdateShaderUniformMat4 e);
            static void UpdateShaderUniform1i(UpdateShaderUniform1i e);
            static void UpdateShaderUniform1f(UpdateShaderUniform1f e);

        private:
            Renderer() = delete;
            static std::queue<std::unique_ptr<RenderCommand>> s_CommandQueue; // write buffer
            static std::queue<std::unique_ptr<RenderCommand>> s_ExecuteQueue; // read buffer
            static std::mutex s_CommandMutex;
            static std::unordered_map<UUID, std::shared_ptr<VertexArray>> s_VaoMap;
            static std::unordered_map<UUID, std::shared_ptr<IndexBuffer>> s_IndexBufferMap;
            static std::unordered_map<UUID, std::shared_ptr<Texture>> s_TextureMap;
            static std::unordered_map<UUID, std::shared_ptr<Shader>> s_ShaderMap;
    };
}
#endif // AGATE_RENDERER_HPP
