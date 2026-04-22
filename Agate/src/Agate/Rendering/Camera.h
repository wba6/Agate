//
// Created by William Aey on 8/15/2022.
//

#pragma once

#include "Agate/Events/Event.h"
#include "Agate/Events/KeyEvents.h"
#include "Agate/Events/MouseEvent.h"
#include "mock/ShaderUser.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Agate {
    class Camera {
    public:
        explicit Camera(ShaderUser &shaderObj);

        void onEvent(Event &ev);

        void onUpdate();

        glm::vec3 getCameraPos();

        void setCameraPos(glm::vec3 pos);

        void setCameraSpeed(float cameraSpeed);

        void SetViewportSize(float width, float height);

    private:
        bool KeyPressed();

        bool releaseCamera(KeyPressedEvent &e);

        bool MouseMove();

    private:
        static float s_lastX, s_lastY, s_yaw, s_pitch, s_fov;
        static bool s_firstMouse;
        static glm::vec3 s_cameraFront;
        float m_cameraSpeed;
        float m_lastFrame;
        bool s_Active;
        ShaderUser &m_Shader;
        glm::mat4 m_projection;
        glm::vec3 m_cameraPos;
        glm::vec3 m_cameraUp;
        glm::mat4 m_view;
        float m_deltaTime;
        float m_viewportWidth = 800.0f;
        float m_viewportHeight = 600.0f;
    };

}// namespace Agate
