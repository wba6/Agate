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
    static constexpr float s_sidePanelMinWidth = 150.0f;
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

    /**
     * @brief Updates the dimensions of the UI panels based on the current window size
     * 
     * @param width Current width of the application window
     * @param height Current height of the application window
     */
    void inline UpdatePanelDimensions(int width, int height);
private:

    // UI Element Dimensions
    float m_topPanelHeight = s_topPanelMaxHeight;
    float m_leftPanelWidth = s_sidePanelMinWidth;
    float m_rightPanelWidth = s_sidePanelMinWidth;
    float m_bottomPanelHeight = s_bottomPanelMinHeight;
    float m_middlePanelHeights = 0.0f;
    float m_middlePanelWidth = 0.0f;

    // UI Data State
    int m_selectedObjectType = 0;
    float m_selectedObjectPosition[3] = { 0.0f, 0.0f, 0.0f };
    float m_selectedObjectRotationRadians = 0.0f;
    float m_selectedObjectScale[3] = { 1.0f, 1.0f, 1.0f };
    int m_selectedObjectColorRGBA[4] = { 255, 255, 255, 255 };

    /**
     * @brief Renders the top UI panel
     */
    void inline RenderTopPanel();

    /**
     * @brief Renders the left UI panel
     */
    void inline RenderLeftPanel();

    /**
     * @brief Renders the center UI panel
     */
    void inline RenderCenterPanel();

    /**
     * @brief Renders the right UI panel
     */
    void inline RenderRightPanel();

    /**
     * @brief Renders the bottom UI panel
     */
    void inline RenderBottomPanel();
};

#endif // AGATE_EDITOR_GUI_LAYER_HPP
