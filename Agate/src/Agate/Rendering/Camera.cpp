//
// Created by William Aey on 8/15/2022.
//
#include "Camera.h"
#include "Agate/Core/InputPulling.h"
#include "Core/EntryPoint.h"
#include "Core/keyCodes.h"
#include "agpch.h"
namespace Agate
{
    float Camera::s_lastX{400.f};
    float Camera::s_lastY{300.f};
    bool Camera::s_firstMouse{true};
    float Camera::s_yaw{-90.f};
    float Camera::s_pitch{0.0f};
    float Camera::s_fov{45.f};
    glm::vec3 Camera::s_cameraFront{glm::vec3(0.0f, 0.0f, -1.0f)};

    Camera::Camera(Shader &shaderObj)
        : s_Active(false), m_deltaTime(0.0f), m_lastFrame(0.0f), m_Shader(shaderObj), m_cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)), m_cameraUp(glm::vec3(0.0f, 1.0f, 0.0f))
    {}

    void Camera::onUpdate()
    {
        MouseMove();
        KeyPressed();
        m_deltaTime = EntryPoint::GetInstance()->GetDeltaTime();
        m_view = glm::lookAt(m_cameraPos, m_cameraPos + s_cameraFront, m_cameraUp);
        m_projection = glm::perspective(glm::radians(s_fov), 800.0f / 600.0f, 0.1f, 100.0f);
        m_Shader.SetUniformMat4("view", m_view);
        m_Shader.SetUniformMat4("projection", m_projection);
    }
    void Camera::onEvent(Event &ev)
    {
        EventNotifier call(ev);
        call.NotifyEvent<KeyPressedEvent>(BindFn(Camera::releaseCamera));
    }

    bool Camera::KeyPressed()
    {
        if (!s_Active)
            return false;
        //TODO: temporary way of handling key presses
        //w = 87 // s = 83 // d = 68 // a == 65
        const float cameraSpeed = 2.5f * m_deltaTime;// adjust accordingly
        if (InputPulling::IsKeyPressed(AGATE_KEY_W))
            m_cameraPos += cameraSpeed * s_cameraFront;
        if (InputPulling::IsKeyPressed(AGATE_KEY_S))
            m_cameraPos -= cameraSpeed * s_cameraFront;
        if (InputPulling::IsKeyPressed(AGATE_KEY_A))
            m_cameraPos -= glm::normalize(glm::cross(s_cameraFront, m_cameraUp)) * cameraSpeed;
        if (InputPulling::IsKeyPressed(AGATE_KEY_D))
            m_cameraPos += glm::normalize(glm::cross(s_cameraFront, m_cameraUp)) * cameraSpeed;
        if (InputPulling::IsKeyPressed(AGATE_KEY_SPACE))
            m_cameraPos += m_cameraUp * cameraSpeed;
        if (InputPulling::IsKeyPressed(AGATE_KEY_LEFT_CONTROL))
            m_cameraPos -= m_cameraUp * cameraSpeed;

        return true;
    }
    bool Camera::MouseMove()
    {
        if (!s_Active)
            return false;
        float xpos = (float) InputPulling::GetXMousePos();
        float ypos = (float) InputPulling::GetYMousePos();
        if (s_firstMouse)// initially set to true
        {
            s_lastX = xpos;
            s_lastY = ypos;
            s_firstMouse = false;
        }
        float xoffset = xpos - s_lastX;
        float yoffset = s_lastY - ypos;// reversed since y-coordinates range from bottom to
        s_lastX = xpos;
        s_lastY = ypos;
        const float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;
        s_yaw += xoffset;
        s_pitch += yoffset;
        if (s_pitch > 89.0f)
            s_pitch = 89.0f;
        if (s_pitch < -89.0f)
            s_pitch = -89.0f;
        glm::vec3 direction;
        direction.x = cos(glm::radians(s_yaw)) * cos(glm::radians(s_pitch));
        direction.y = sin(glm::radians(s_pitch));
        direction.z = sin(glm::radians(s_yaw)) * cos(glm::radians(s_pitch));
        s_cameraFront = glm::normalize(direction);
        return true;
    }
    bool Camera::releaseCamera(KeyPressedEvent &e)
    {

        if ((e.GetKeyCode() == AGATE_KEY_ESCAPE) && !s_Active)
        {
            Agate::EntryPoint::GetInstance()->GetWindow()->GrabCursor(true);
            s_Active = true;
            s_firstMouse = true;
            return true;
        }
        else if (s_Active && (e.GetKeyCode() == AGATE_KEY_ESCAPE))
        {
            Agate::EntryPoint::GetInstance()->GetWindow()->GrabCursor(false);
            s_Active = false;
            return true;
        }
        return false;
    }
    glm::vec3 Camera::getCameraPos()
    {
        return m_cameraPos;
    }
    void Camera::setCameraPos(glm::vec3 pos)
    {
        m_cameraPos = pos;
    }
}// namespace Agate
