/**
 * @brief Implementation file for the GuiLayer class
 */

#include "GuiLayer.hpp"
#include "Agate/Rendering/Renderer.hpp"
#include "Agate/Events/RenderCommand.hpp"

constexpr inline ImGuiWindowFlags removeWindowDecorationFlags() {
    return ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | 
           ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | 
           ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | 
           ImGuiWindowFlags_NoBackground;
}

GuiLayer::GuiLayer(std::shared_ptr<Agate::Window> window) {
    window->SetMinimumSize(s_minimumWindowWidth, s_minimumWindowHeight);
}

void GuiLayer::Attach() {
    PRINTMSG("Attaching GUI layer");
    m_scene->Prepare();
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

    if (m_middlePanelHeights > 0.0f) {
        RenderLeftPanel();
        if (m_middlePanelWidth > 0.0f) {
            ImGui::SameLine(0.0f, 0.0f);
            RenderCenterPanel();
        }
        ImGui::SameLine(0.0f, 0.0f);
        RenderRightPanel();
    }
    RenderBottomPanel();

    ImGui::End();
}

void GuiLayer::OnEvent(Agate::Event &e) {
    m_scene->OnEvent(e);
}

void GuiLayer::OnUpdate() {

}

void GuiLayer::UpdatePanelDimensions() {
    
    // Element heights
    auto [width, height] = ImGui::GetContentRegionAvail();
    float remainingHeight = height;
    m_topPanelHeight = s_topPanelHeight;
    remainingHeight -= m_topPanelHeight;
    m_bottomPanelHeight = std::max(s_bottomPanelMinHeight, std::min(remainingHeight, m_bottomPanelHeight));
    remainingHeight -= m_bottomPanelHeight;
    m_middlePanelHeights = remainingHeight;

    // Element widths
    float remainingWidth = width;
    m_leftPanelWidth = std::max(s_sidePanelMinWidth, std::min(remainingWidth - s_sidePanelMinWidth, m_leftPanelWidth));
    remainingWidth -= m_leftPanelWidth;
    m_rightPanelWidth = std::max(s_sidePanelMinWidth, std::min(remainingWidth, m_rightPanelWidth));
    remainingWidth -= m_rightPanelWidth;
    m_middlePanelWidth = remainingWidth;

    // Resize frame buffer
    m_sceneFrameBuffer->Resize(static_cast<unsigned int>(m_middlePanelWidth), static_cast<unsigned int>(m_middlePanelHeights));
    m_scene->SetViewportSize(m_middlePanelWidth, m_middlePanelHeights);
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
    ImGui::Combo("##ObjectType", &m_selectedObjectType, "Type One\0Type Two\0Type Three\0");

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    ImGui::EndChild();
    ImGui::PopStyleVar();
}

void GuiLayer::RenderCenterPanel() {

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    ImGui::BeginChild("CenterPanel", ImVec2(m_middlePanelWidth, m_middlePanelHeights), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::PopStyleVar();


    m_sceneFrameBuffer->Bind();
    Agate::Renderer::Submit(std::make_unique<Agate::Clear>(0.65f, 0.7f, 0.8f, 1.0f));
    Agate::Renderer::Submit(std::make_unique<Agate::SetViewport>(0, 0, static_cast<uint32_t>(m_middlePanelWidth), static_cast<uint32_t>(m_middlePanelHeights)));
    m_scene->Render();
    m_sceneFrameBuffer->UnBind();

    unsigned int textureId = Agate::Renderer::GetFrameBufferTexture(m_sceneFrameBuffer->getUUID());
    if (textureId) {
        ImGui::Image((void*)(uintptr_t)textureId, ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
    } else {
        ImGui::Text("Scene Viewport (Initializing...)");
    }

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
    ImGui::InputFloat("X##Position", &m_selectedObjectPosition[0], 0.0f, 0.0f, "%.2f");
    ImGui::InputFloat("Y##Position", &m_selectedObjectPosition[1], 0.0f, 0.0f, "%.2f");
    ImGui::InputFloat("Z##Position", &m_selectedObjectPosition[2], 0.0f, 0.0f, "%.2f");
    ImGui::Text("Rotation");
    ImGui::SliderAngle("##RotationAngle", &m_selectedObjectRotationRadians);
    ImGui::Text("Scale");
    ImGui::InputFloat("X##Scale", &m_selectedObjectScale[0], 0.0f, 0.0f, "%.2f");
    ImGui::InputFloat("Y##Scale", &m_selectedObjectScale[1], 0.0f, 0.0f, "%.2f");
    ImGui::InputFloat("Z##Scale", &m_selectedObjectScale[2], 0.0f, 0.0f, "%.2f");
    ImGui::Separator();
    if (ImGui::Button("Apply Transform", ImVec2(-1, 0))) {
        ApplyTransform();
    }
    // ImGui::Text("Albedo");
    // ImGui::SliderInt("R", &m_selectedObjectColorRGBA[0], 0, 255);
    // ImGui::SliderInt("G", &m_selectedObjectColorRGBA[1], 0, 255);
    // ImGui::SliderInt("B", &m_selectedObjectColorRGBA[2], 0, 255);
    // ImGui::SliderInt("A", &m_selectedObjectColorRGBA[3], 0, 255);

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

void GuiLayer::ApplyTransform() {

    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(
        m_selectedObjectPosition[0],
        m_selectedObjectPosition[1],
        m_selectedObjectPosition[2]
    ));
    transform = glm::rotate(
        transform,
        m_selectedObjectRotationRadians,
        glm::vec3(0.0f, 1, 0)
    );
    transform = glm::scale(transform, glm::vec3(
        m_selectedObjectScale[0],
        m_selectedObjectScale[1],
        m_selectedObjectScale[2]
    ));

    m_scene->SetModelTransform(transform);
}
