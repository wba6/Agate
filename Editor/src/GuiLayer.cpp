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
    ImGui::Begin("MainWindow", nullptr, removeWindowDecorationFlags());
    ImGui::PopStyleVar();

    RenderTopPanel();
    RenderLeftPanel();
    ImGui::SameLine();
    RenderCenterPanel();
    RenderRightPanel();
    RenderBottomPanel();

    ImGui::End();
}

void GuiLayer::OnEvent(Agate::Event &e) {

    Agate::EventNotifier notifier(e);
    notifier.NotifyEvent<Agate::WindowResizedEvent>([this](Agate::WindowResizedEvent &e) {
        const auto [width, height] = e.GetWindowSize();
        UpdatePanelDimensions(width, height);
        PRINTMSG(
            "New Dims: Top={}x{}, Left={}x{}, Right={}x{}, Bottom={}x{}, Middle={}x{}",
            m_topPanelHeight, width,
            m_middlePanelHeights, m_leftPanelWidth,
            m_middlePanelHeights, m_rightPanelWidth,
            m_bottomPanelHeight, width,
            m_middlePanelHeights, m_middlePanelWidth
        );
        return true;
    });
}

void GuiLayer::UpdatePanelDimensions(int width, int height) {
    
    // Element heights
    float remainingHeight = static_cast<float>(height);
    m_topPanelHeight = std::clamp(remainingHeight, s_topPanelMinHeight, s_topPanelMaxHeight);
    remainingHeight -= m_topPanelHeight;
    m_bottomPanelHeight = std::clamp(m_bottomPanelHeight, s_bottomPanelMinHeight, remainingHeight);
    remainingHeight -= m_bottomPanelHeight;
    m_middlePanelHeights = remainingHeight;

    // Element widths
    float remainingWidth = static_cast<float>(width);
    m_leftPanelWidth = std::clamp(m_leftPanelWidth, s_sidePanelMinWidth, remainingWidth - s_sidePanelMinWidth);
    remainingWidth -= m_leftPanelWidth;
    m_rightPanelWidth = std::clamp(m_rightPanelWidth, s_sidePanelMinWidth, remainingWidth - s_sidePanelMinWidth);
    remainingWidth -= m_rightPanelWidth;
    m_middlePanelWidth = remainingWidth;
}

void GuiLayer::RenderTopPanel() {
    ImGui::BeginChild("TopPanel", ImVec2(0, m_topPanelHeight), true);

    // Placeholder elements
    ImGui::Button("File");
    ImGui::SameLine();
    ImGui::Button("Edit");
    ImGui::SameLine();
    ImGui::Button("Help");

    ImGui::EndChild();
}

void GuiLayer::RenderLeftPanel() {
    ImGui::BeginChild("LeftPanel", ImVec2(m_leftPanelWidth, m_middlePanelHeights), true);

    // Placeholder elements
    ImGui::Text("Left Side Menu");
    ImGui::Separator();
    ImGui::Button("Object One", ImVec2(-1, 0));
    ImGui::Button("Object Two", ImVec2(-1, 0));
    ImGui::Button("Object Three", ImVec2(-1, 0));
    ImGui::Separator();
    ImGui::Text("Object Type");
    ImGui::Combo("##", &m_SelectedObjectType, "Type One\0Type Two\0Type Three\0");

    ImGui::EndChild();
}

void GuiLayer::RenderCenterPanel() {
    ImGui::BeginChild("CenterPanel", ImVec2(m_middlePanelWidth, m_middlePanelHeights), true);

    // Placeholder elements
    ImGui::Text("Scene Viewport");

    ImGui::EndChild();
}

void GuiLayer::RenderRightPanel() {

}

void GuiLayer::RenderBottomPanel() {

}
