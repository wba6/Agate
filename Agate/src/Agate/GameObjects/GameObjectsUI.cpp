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
        if (ImGui::CollapsingHeader((m_gameobjects.at(i)->GetObjectString() + std::to_string(m_gameobjects.at(i)->GetInstanceNumber())).c_str()))
        {
            ImGui::Text("Positions");
            ImGui::Separator();
            ImGui::Text("xPos");
            ImGui::SameLine();
            ImGui::InputFloat(",", &m_gameobjects.at(i)->x, 1);
            ImGui::Text("yPos");
            ImGui::SameLine();
            ImGui::InputFloat(";", &m_gameobjects.at(i)->y, 1);
        }
    }
    ImGui::End();
}
void Agate::GameObjectsUI::AddObject(Agate::GameObject *go)
{
    m_gameobjects.push_back(go);
}

