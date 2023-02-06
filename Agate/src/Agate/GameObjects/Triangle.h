//
// Created by TANK1_41 on 9/26/2022.
//

#ifndef AGATE_TRIANGLE_H
#define AGATE_TRIANGLE_H
#include "Agate/Core/Layer.h"
#include "Agate/Rendering/OpenGl/IndexBuffer.h"
#include "Agate/Rendering/OpenGl/Shader.h"
#include "Agate/Rendering/OpenGl/VertexArray.h"
#include "Agate/Rendering/OpenGl/VertexBuffer.h"
#include "GameObject.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Agate
{

    class Triangle : public Layer, public GameObject {
    public:
        Triangle(int xpos = 0, int ypos = 0);
        virtual ~Triangle();
        void OnEvent(Event &e) override;
        GameObjectType GetObjectType() override;
        std::string GetObjectString() override;


        void Render() override;

        void setColor(int r, int g, int b, int a);



    private:
        std::vector<float> vertices = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f};
        std::vector<unsigned int> indices{
                0, 1, 2};
        VertexLayOut layout;
        IndexBuffer IBO;
        VertexBuffer VBO;
        VertexArray *VAO;
        Shader shader;
        static int s_instanceNumberCounter;
        friend class Render;
    };
}// namespace Agate

#endif//AGATE_TRIANGLE_H
