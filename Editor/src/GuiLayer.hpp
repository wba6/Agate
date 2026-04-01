/**
 * @brief Include file for the GuiLayer class, which defines the primary GUI for the editor
 */

#ifndef AGATE_EDITOR_GUI_LAYER_HPP
#define AGATE_EDITOR_GUI_LAYER_HPP

#include "Agate.h"

class GuiLayer : public Agate::Layer {
private:
    static constexpr float s_topPanelMinHeight = 20.0f;
    static constexpr float s_topPanelMaxHeight = 50.0f;
    static constexpr float s_sidePanelMinWidth = 80.0f;
    static constexpr float s_bottomPanelMinHeight = 30.0f;
public:
    void Attach() override;

    void Detach() override;

    void OnRender() override;

    void OnEvent(Agate::Event &e) override;
private:
    float m_topPanelHeight = s_topPanelMinHeight;
    float m_leftPanelWidth = s_sidePanelMinWidth;
    float m_rightPanelWidth = s_sidePanelMinWidth;
    float m_bottomPanelHeight = s_bottomPanelMinHeight;
    void RenderTopPanel();
    void RenderLeftPanel();
    void RenderCenterPanel();
    void RenderRightPanel();
    void RenderBottomPanel();
};

#endif // AGATE_EDITOR_GUI_LAYER_HPP
