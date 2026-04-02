/**
 * @brief Implementation file for the GuiLayer class
 */

#include "GuiLayer.hpp"

constexpr inline ImGuiWindowFlags removeWindowDecorationFlags() {
    return ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | 
           ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | 
           ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | 
           ImGuiWindowFlags_NoBackground;
}

void GuiLayer::Attach() {
    PRINTMSG("Attaching GUI layer");
}

void GuiLayer::Detach() {
    PRINTMSG("Detaching GUI layer");
}

void GuiLayer::OnRender() {

    // Main window - No padding and no decoration
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    ImGui::Begin("MainWindow", nullptr, removeWindowDecorationFlags());
    ImGui::PopStyleVar();
    ImGui::PopStyleVar();

    UpdatePanelDimensions();
    RenderTopPanel();
    RenderLeftPanel();
    ImGui::SameLine(0.0f, 0.0f);
    RenderCenterPanel();
    ImGui::SameLine(0.0f, 0.0f);
    RenderRightPanel();
    RenderBottomPanel();

    ImGui::End();
}

void GuiLayer::OnEvent(Agate::Event &e) {

}

void GuiLayer::UpdatePanelDimensions() {
    
    // Element heights
    auto [width, height] = ImGui::GetContentRegionAvail();
    float remainingHeight = height;
    m_topPanelHeight = std::clamp(remainingHeight, s_topPanelMinHeight, s_topPanelMaxHeight);
    remainingHeight -= m_topPanelHeight;
    m_bottomPanelHeight = std::clamp(m_bottomPanelHeight, s_bottomPanelMinHeight, remainingHeight);
    remainingHeight -= m_bottomPanelHeight;
    m_middlePanelHeights = remainingHeight;

    // Element widths
    float remainingWidth = width;
    m_leftPanelWidth = std::clamp(m_leftPanelWidth, s_sidePanelMinWidth, remainingWidth - s_sidePanelMinWidth);
    remainingWidth -= m_leftPanelWidth;
    m_rightPanelWidth = std::clamp(m_rightPanelWidth, s_sidePanelMinWidth, std::max(remainingWidth - s_sidePanelMinWidth, s_sidePanelMinWidth));
    remainingWidth -= m_rightPanelWidth;
    m_middlePanelWidth = remainingWidth;
}

void GuiLayer::RenderTopPanel() {

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    ImGui::BeginChild("TopPanel", ImVec2(0, m_topPanelHeight), true);
    ImGui::PopStyleVar();

    // Placeholder elements
    ImGui::Button("File");
    ImGui::SameLine();
    ImGui::Button("Edit");
    ImGui::SameLine();
    ImGui::Button("Help");

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    ImGui::EndChild();
    ImGui::PopStyleVar();
}

void GuiLayer::RenderLeftPanel() {

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    ImGui::BeginChild("LeftPanel", ImVec2(m_leftPanelWidth, m_middlePanelHeights), true);
    ImGui::PopStyleVar();

    // Placeholder elements
    ImGui::Text("Left Side Menu");
    ImGui::Separator();
    ImGui::Button("Object One", ImVec2(-1, 0));
    ImGui::Button("Object Two", ImVec2(-1, 0));
    ImGui::Button("Object Three", ImVec2(-1, 0));
    ImGui::Separator();
    ImGui::Text("Object Type");
    ImGui::Combo("##", &m_selectedObjectType, "Type One\0Type Two\0Type Three\0");

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    ImGui::EndChild();
    ImGui::PopStyleVar();
}

void GuiLayer::RenderCenterPanel() {

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    ImGui::BeginChild("CenterPanel", ImVec2(m_middlePanelWidth, m_middlePanelHeights), true);
    ImGui::PopStyleVar();

    // Placeholder elements
    ImGui::Text("Scene Viewport");

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    ImGui::EndChild();
    ImGui::PopStyleVar();
}

void GuiLayer::RenderRightPanel() {

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    ImGui::BeginChild("RightPanel", ImVec2(m_rightPanelWidth, m_middlePanelHeights), true);
    ImGui::PopStyleVar();

    // Placeholder elements
    ImGui::Text("Right Side Menu");
    ImGui::Separator();
    ImGui::Text("Position");
    ImGui::InputFloat("X", &m_selectedObjectPosition[0], 0.0f, 0.0f, "%.2f");
    ImGui::InputFloat("Y", &m_selectedObjectPosition[1], 0.0f, 0.0f, "%.2f");
    ImGui::InputFloat("Z", &m_selectedObjectPosition[2], 0.0f, 0.0f, "%.2f");
    ImGui::Text("Rotation");
    ImGui::SliderAngle("##", &m_selectedObjectRotationRadians);
    ImGui::Text("Scale");
    ImGui::InputFloat("X", &m_selectedObjectScale[0], 0.0f, 0.0f, "%.2f");
    ImGui::InputFloat("Y", &m_selectedObjectScale[1], 0.0f, 0.0f, "%.2f");
    ImGui::InputFloat("Z", &m_selectedObjectScale[2], 0.0f, 0.0f, "%.2f");
    ImGui::Separator();
    ImGui::Text("Albedo");
    ImGui::SliderInt("R", &m_selectedObjectColorRGBA[0], 0, 255);
    ImGui::SliderInt("B", &m_selectedObjectColorRGBA[1], 0, 255);
    ImGui::SliderInt("G", &m_selectedObjectColorRGBA[2], 0, 255);
    ImGui::SliderInt("A", &m_selectedObjectColorRGBA[3], 0, 255);

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    ImGui::EndChild();
    ImGui::PopStyleVar();
}

void GuiLayer::RenderBottomPanel() {

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    ImGui::BeginChild("BottomPanel", ImVec2(0, m_bottomPanelHeight), true);
    ImGui::PopStyleVar();

    // Placeholder elements
    ImGui::Button("Output");
    ImGui::SameLine();
    ImGui::Button("Console");
    ImGui::SameLine();
    ImGui::Button("Errors");

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    ImGui::EndChild();
    ImGui::PopStyleVar();
}
