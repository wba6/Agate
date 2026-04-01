/**
 * @brief Implementation file for the GuiLayer class
 */

#include "GuiLayer.hpp"

void GuiLayer::Attach() {
    PRINTMSG("Attaching GUI layer");
}

void GuiLayer::Detach() {
    PRINTMSG("Detaching GUI layer");
}

void GuiLayer::OnRender() {
    RenderTopPanel();
    RenderLeftPanel();
    RenderCenterPanel();
    RenderRightPanel();
    RenderBottomPanel();
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
            m_middlePanelHeights, m_middlePaneWidth
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
    m_middlePaneWidth = remainingWidth;
}

void GuiLayer::RenderTopPanel() {

}

void GuiLayer::RenderLeftPanel() {

}

void GuiLayer::RenderCenterPanel() {

}

void GuiLayer::RenderRightPanel() {

}

void GuiLayer::RenderBottomPanel() {

}
