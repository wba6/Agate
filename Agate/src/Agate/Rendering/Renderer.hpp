#include <memory.h>
#include <queue>
#include "Event.h"
#include "RenderCommand.hpp"

#ifndef AGATE_RENDERER_HPP
#define AGATE_RENDERER_HPP

namespace Agate {

    class Renderer {
        public:

            // Adds a render command to the queue
            static void Submit(std::unique_ptr<RenderCommand> e);

            // Iterates queue and executes opengl commands
            static void Flush();
        private:
            static std::queue<std::unique_ptr<RenderCommand>> s_CommandQueue;
    };
}
#endif // AGATE_RENDERER_HPP
