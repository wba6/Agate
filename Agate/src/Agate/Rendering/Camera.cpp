//
// Created by William Aey on 8/15/2022.
//
#include "agpch.h"
#include "Camera.h"
#include "Core/EntryPoint.h"
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
        : m_deltaTime(0.0f), m_lastFrame(0.0f), m_Shader(shaderObj), m_cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)), m_cameraUp(glm::vec3(0.0f, 1.0f, 0.0f))
    {}

    void Camera::onUpdate()
    {
        m_deltaTime = EntryPoint::GetInstance()->GetDeltaTime();
        m_view = glm::lookAt(m_cameraPos, m_cameraPos + s_cameraFront, m_cameraUp);
        m_projection = glm::perspective(glm::radians(s_fov), 800.0f / 600.0f, 0.1f, 100.0f);
        m_Shader.SetUniformMat4("view", m_view);
        m_Shader.SetUniformMat4("projection", m_projection);
    }
    void Camera::onEvent(Event &ev)
    {
        EventNotifier call(ev);
        call.NotifyEvent<KeyPressedEvent>(BindFn(Camera::KeyPess));
        call.NotifyEvent<MouseMoved>(BindFn(Camera::MouseMove));
    }

    bool Camera::KeyPess(KeyPressedEvent &ev)
    {
        //TODO: temporary way of handling key presses
        //w = 87 // s = 83 // d = 68 // a == 65
        unsigned int keyCode = ev.GetKeyCode();
        const float cameraSpeed = 2.5f * m_deltaTime;// adjust accordingly
        if (keyCode == 87)
            m_cameraPos += cameraSpeed * s_cameraFront;
        if (keyCode == 83)
            m_cameraPos -= cameraSpeed * s_cameraFront;
        if (keyCode == 65)
            m_cameraPos -= glm::normalize(glm::cross(s_cameraFront, m_cameraUp)) * cameraSpeed;
        if (keyCode == 68)
            m_cameraPos += glm::normalize(glm::cross(s_cameraFront, m_cameraUp)) * cameraSpeed;
        return false;
    }
    bool Camera::MouseMove(MouseMoved &ev)
    {
        int xpos = ev.GetXPos();
        int ypos = ev.GetYPos();
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
        return false;
    }
}// namespace Agate
