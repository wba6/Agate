//
// Created by TANK1_41 on 9/20/2022.
//

#pragma once
#include "Agate/GameObjects/Triangle.h"
#include "Agate/GameObjects/Square.h"
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

namespace Agate
{
    class Render {
    public:
        Render() = default;
        static void IndexRender(VertexArray*& vao,VertexBuffer& vbo, IndexBuffer& ibo,Shader& shader);
        static long int GetRenderedFrames();
    private:
        static long int framesRendered;
    };
}// namespace Agate