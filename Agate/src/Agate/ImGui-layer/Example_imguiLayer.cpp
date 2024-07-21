//
// Created by William Aey on 8/31/2022.
//
#include "agpch.h"

#include "Example_imguiLayer.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

#include "imgui_interface.h"


void Agate::Example_imguiLayer::Attach() {
}

void Agate::Example_imguiLayer::Detach() {
}

void Agate::Example_imguiLayer::OnEvent(Agate::Event &e) {
}

void Agate::Example_imguiLayer::OnRender() {

    static bool show_demo_window = true;
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);
}

Agate::Example_imguiLayer::Example_imguiLayer() {
}
