//
// Created by TANK1_41 on 9/15/2022.
//

#pragma once
//TODO:TEMP INCLUDE
#include "../Layer.h"
#include "Agate/Rendering/OpenGl/Shader.h"
#include "Agate/Rendering/OpenGl/VertexArray.h"
#include "Agate/Rendering/OpenGl/VertexBuffer.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
namespace Agate
{


    class TemplayerEx : public Layer {

    public:
        TemplayerEx() = default;

        void Attach() override
        {
            PRINTMSG("Attached example layer")
            VBO = new VertexBuffer(vertices, sizeof(vertices), STATIC_DRAW);
            VBO->Bind();

            VertexLayOut vaData{0, 3, false, 3 * sizeof(float), 0};
            VAO = new VertexArray(vaData);
            VAO->Bind();
            shader.bind();
        }

        void Detach() override
        {
        }
        void onRender() override
        {
            rotationMat4 = glm::rotate(rotationMat4, (float) glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));
            shader.SetUniform4f("Ucolors", cos(glfwGetTime()), 0.2f, 0.2f, 1.0f);
            shader.SetUniformMat4("rotation", rotationMat4);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        };
        void OnEvent(Agate::Event &e) override
        {
        }
        virtual ~TemplayerEx()
        {
            delete VAO;
            delete VBO;
        }
        VertexArray *VAO;
        VertexBuffer *VBO;
        glm::mat4 rotationMat4{1.0f};
        Agate::Shader shader = Agate::Shader("Shaders/Basic.vs.shader", "Shaders/Basic.fg.shader");
        float vertices[9] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f};
    };
}