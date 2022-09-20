//
// Created by TANK1_41 on 9/20/2022.
//

#pragma once
#include "Shader.h"
#include "VertexArray.h"
namespace Agate
{
    class Render {
    public:
        Render() = default;
        void RenderTriangles(int indices);
    };
}// namespace Agate