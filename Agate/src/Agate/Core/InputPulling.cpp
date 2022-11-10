//
// Created by william on 11/3/22.
//
#include "InputPulling.h"
#include "EntryPoint.h"
#include <GLFW/glfw3.h>
bool InputPulling::IsKeyPressed(unsigned int keycode)
{
    int state = glfwGetKey((GLFWwindow *) Agate::EntryPoint::GetInstance()->GetWindow()->GetInstanceWindow(), keycode);
    if (state == GLFW_PRESS)
    {
        return true;
    }
    return false;
}
