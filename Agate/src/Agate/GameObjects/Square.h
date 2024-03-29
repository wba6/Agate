//
// Created by William Aey on 10/17/2022.
//

#ifndef AGATE_SQUARE_H
#define AGATE_SQUARE_H
#include "Agate/Core/Layer.h"
#include "Agate/Rendering/Camera.h"
#include "Agate/Rendering/OpenGl/IndexBuffer.h"
#include "Agate/Rendering/OpenGl/Shader.h"
#include "Agate/Rendering/OpenGl/VertexArray.h"
#include "Agate/Rendering/OpenGl/VertexBuffer.h"
#include "GameObject.h"


namespace Agate
{

    class Square : public Layer, public GameObject {
    public:
        explicit Square(int xpos = 0, int ypos = 0, int zpos = 0);
        ~Square() override;
        virtual void OnEvent(Event &e) override;
        virtual GameObjectType GetObjectType() override;
        std::string GetObjectString() override;

        void Render() override;
        void setColor(int r, int g, int b, int a);


    private:
        std::vector<float> vertices = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.5f, 0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f};

        std::vector<unsigned int> indices{
                0, 1, 2,
                2, 3, 0};

        VertexLayOut m_layout;
        IndexBuffer IBO;
        VertexBuffer VBO;
        VertexArray *VAO;
        Shader m_shader;
        static int s_instanceNumberCounter;
        friend class Render;
    };

}// namespace Agate

#endif//AGATE_SQUARE_H
