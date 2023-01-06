//
// Created by William Aey on 12/20/2022.
//

#include "GameObjectsUI.h"
#include "../GameObject.h"
#include <gtc/type_ptr.hpp>
#include <imgui.h>


std::vector<Agate::GameObject *> Agate::GameObjectsUI::m_gameobjects;


Agate::GameObjectsUI::GameObjectsUI() = default;
void Agate::GameObjectsUI::OnRender()
{
    ImGui::Begin("GameObjects");
    for (int i = 0; i < m_gameobjects.size(); ++i)
    {
        if (ImGui::CollapsingHeader((m_gameobjects.at(i)->GetObjectString() + std::to_string(m_gameobjects.at(i)->GetInstanceNumber())).c_str()))
        {
            /*
             * TODO: Will crash if multiple headers are open and you modify color
             *
             * */

            ImGui::Text("Positions:");
            ImGui::Separator();
            ImGui::Text("xPos");
            ImGui::SameLine();
            ImGui::InputFloat(",", &m_gameobjects.at(i)->x, 1);
            ImGui::Text("yPos");
            ImGui::SameLine();
            ImGui::InputFloat(";", &m_gameobjects.at(i)->y, 1);
            ImGui::Text("Color:");
            ImGui::SameLine();
            ImGui::ColorEdit4("##RefColor", glm::value_ptr(m_gameobjects.at(i)->color));
        }
    }
    ImGui::End();
}
void Agate::GameObjectsUI::AddObject(Agate::GameObject *go)
{
    m_gameobjects.push_back(go);
}
