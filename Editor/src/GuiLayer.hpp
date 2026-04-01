/**
 * @brief Include file for the GuiLayer class, which defines the primary GUI for the editor
 */

#ifndef AGATE_EDITOR_GUI_LAYER_HPP
#define AGATE_EDITOR_GUI_LAYER_HPP

#include "Agate.h"

/**
 * @brief Layer that renders the editor's GUI elements and controls
 * 
 * Directly renders the editor's menus and containers, then passes the rendered
 * scene to the center panel for drawing
 */
class GuiLayer : public Agate::Layer {
private:
    static constexpr float s_topPanelMinHeight = 20.0f;
    static constexpr float s_topPanelMaxHeight = 50.0f;
    static constexpr float s_sidePanelMinWidth = 80.0f;
    static constexpr float s_bottomPanelMinHeight = 30.0f;
public:

    /**
     * @brief Called immediately after being added to the 
     *        layer stack
     */
    void Attach() override;

    /**
     * @brief Called immediately before being removed from
     *        the layer stack
     */
    void Detach() override;

    /**
     * @brief Called once every render frame
     */
    void OnRender() override;

    /**
     * @brief Event handler for this layer
     * 
     * @param e Event to handle
     */
    void OnEvent(Agate::Event &e) override;
private:
    float m_topPanelHeight = s_topPanelMinHeight;
    float m_leftPanelWidth = s_sidePanelMinWidth;
    float m_rightPanelWidth = s_sidePanelMinWidth;
    float m_bottomPanelHeight = s_bottomPanelMinHeight;

    /**
     * @brief Renders the top UI panel
     */
    void RenderTopPanel();

    /**
     * @brief Renders the left UI panel
     */
    void RenderLeftPanel();

    /**
     * @brief Renders the center UI panel
     */
    void RenderCenterPanel();

    /**
     * @brief Renders the right UI panel
     */
    void RenderRightPanel();

    /**
     * @brief Renders the bottom UI panel
     */
    void RenderBottomPanel();
};

#endif // AGATE_EDITOR_GUI_LAYER_HPP
