//
// Created by TANK1_41 on 9/20/2022.
//

#pragma once
#include "Shader.h"
#include "VertexArray.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

namespace Agate
{
    class Render {
    public:
        Render() = default;
        void RenderTriagle(const std::vector<float>& vertices, VertexLayOut layout, glm::vec4 color, int rotation);
    };
}// namespace Agate