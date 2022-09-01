//
// Created by William Aey on 8/31/2022.
//
#include "agpch.h"

#include "imguiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include "glad/glad.h"

void Agate::imguiLayer::Attach()
{
    PRINTMSG("Attached im");
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;// Enable Multi-Viewport / Platform Windows
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    // When view ports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)m_glfwWindow, true);
    ImGui_ImplOpenGL3_Init("#version 430");

}
void Agate::imguiLayer::Detach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
void Agate::imguiLayer::OnEvent(Agate::Event &e)
{
}
void Agate::imguiLayer::onRender()
{

    static bool show_demo_window = true;
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);


}
Agate::imguiLayer::imguiLayer(void *GlfwWindow)
:m_glfwWindow(GlfwWindow)
{
}
void Agate::imguiLayer::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}
void Agate::imguiLayer::End()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::Render();
    //TODO: finish adding information here
}
