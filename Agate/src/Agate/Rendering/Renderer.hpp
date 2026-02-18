
#ifndef AGATE_RENDERER_HPP
#define AGATE_RENDERER_HPP

#include <memory.h>
#include <queue>
#include "Event.h"
#include "RenderCommand.hpp"

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
        private:
            Renderer() = delete;
            static std::queue<std::unique_ptr<RenderCommand>> s_CommandQueue;
    };
}
#endif // AGATE_RENDERER_HPP
