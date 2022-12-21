//
// Created by William Aey on 12/20/2022.
//

#include "GameObjectsUI.h"
#include "../../../vender/imgui/imgui.h"
std::vector<Agate::GameObject*> Agate::GameObjectsUI::m_gameobjects;


Agate::GameObjectsUI::GameObjectsUI() = default;
void Agate::GameObjectsUI::OnRender()
{
    ImGui::Begin("GameObjects");
    for (int i = 0; i < m_gameobjects.size(); ++i)
    {
        if (ImGui::CollapsingHeader(m_gameobjects.at(i)->GetObjectString()))
        {
            ImGui::Text("Positions");
            ImGui::BulletText("%s", ("Xpos: " + std::to_string(m_gameobjects.at(i)->x)).c_str());

            ImGui::Separator();

            ImGui::Text("PROGRAMMER GUIDE:");
            ImGui::BulletText("See the ShowDemoWindow() code in imgui_demo.cpp. <- you are here!");
            ImGui::BulletText("See comments in imgui.cpp.");
            ImGui::BulletText("See example applications in the examples/ folder.");
            ImGui::BulletText("Read the FAQ at http://www.dearimgui.org/faq/");
            ImGui::BulletText("Set 'io.ConfigFlags |= NavEnableKeyboard' for keyboard controls.");
            ImGui::BulletText("Set 'io.ConfigFlags |= NavEnableGamepad' for gamepad controls.");
            ImGui::Separator();

            ImGui::Text("USER GUIDE:");
            ImGui::ShowUserGuide();
        }
    }
    ImGui::End();
}
void Agate::GameObjectsUI::AddObject(Agate::GameObject *go)
{
    m_gameobjects.push_back(go);
}

