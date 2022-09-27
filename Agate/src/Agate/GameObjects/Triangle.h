//
// Created by TANK1_41 on 9/26/2022.
//

#ifndef AGATE_TRIANGLE_H
#define AGATE_TRIANGLE_H
#include "Agate/Layer.h"
#include "Agate/Rendering/OpenGl/VertexArray.h"
#include "Agate/Rendering/OpenGl/VertexBuffer.h"
#include "Agate/Rendering/OpenGl/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Agate
{

    class Triangle : public Layer {
    public:
        Triangle(int xpos, int ypos);
        Triangle();
        void OnEvent(Event &e) override;
        void OnRender() override;

        void setXPos(int xPos);
        void setYPos(int yPos);

        int x, y;
        float rotation;
        glm::vec4 color;

    private:
        std::vector<float> vertices = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f};

        VertexLayOut layout;

        VertexBuffer VBO;
        std::unique_ptr<VertexArray> VAO;
        Shader shader;
        friend class Render;
    };
}// namespace Agate

#endif//AGATE_TRIANGLE_H
