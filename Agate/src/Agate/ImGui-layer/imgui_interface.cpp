//
// Created by TANK1_41 on 10/31/2022.
//
#include "agpch.h"

#include "Agate/Core/Logger.h"
#include "imgui_interface.h"
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

namespace Agate {
    void imgui_interface::Init(void *window) {
        static bool status;
        if (status) {
            PRINTCRIT("IMGUI already init");
            return;
        }
        PRINTMSG("Attached imgui");
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
        ImGui::StyleColorsClassic();
        //ImGui::StyleColorsClassic();
        // When view ports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle &style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow *) window, true);
        ImGui_ImplOpenGL3_Init("#version 150");
        status = true;
    }

    void imgui_interface::ImguiDestruct() {
        static bool status;
        if (status) {
            PRINTCRIT("IMGUI already destructed");
            return;
        }
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        status = true;
    }

    void imgui_interface::BeginFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void imgui_interface::EndFrame() {
        ImGui::Render();
    }

    void imgui_interface::Render_GPU() {
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}// namespace Agate
