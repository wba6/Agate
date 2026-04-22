/**
 * @brief Include file for the GuiLayer class, which defines the primary GUI for the editor
 */

#ifndef AGATE_EDITOR_GUI_LAYER_HPP
#define AGATE_EDITOR_GUI_LAYER_HPP

#include "Agate.h"
#include "Scene.hpp"
#include <memory>

/**
 * @brief Layer that renders the editor's GUI elements and controls
 * 
 * Directly renders the editor's menus and containers, then passes the rendered
 * scene to the center panel for drawing
 */
class GuiLayer : public Agate::Layer {
private:
    static constexpr float s_topPanelHeight = 40.0f;
    static constexpr float s_sidePanelMinWidth = 150.0f;
    static constexpr float s_bottomPanelMinHeight = 40.0f;
    static constexpr float s_minimumWindowWidth = 2.0f * s_sidePanelMinWidth;
    static constexpr float s_minimumWindowHeight = s_topPanelHeight + s_bottomPanelMinHeight;
public:

    /**
     * @brief Constructor - Sets minimum window size
     *        to prevent resizing
     */
    GuiLayer(std::shared_ptr<Agate::Window> window);

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
     * @brief Called once every game loop 
     */
    void OnUpdate() override;

    /**
     * @brief Updates the dimensions of the UI panels based on the current window size
     */
    void inline UpdatePanelDimensions();
private:

    // UI Element Dimensions
    float m_topPanelHeight = s_topPanelHeight;
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

    // Scene Data
    std::unique_ptr<Scene> m_scene = std::make_unique<Scene>();
    std::unique_ptr<Agate::FrameBufferUser> m_sceneFrameBuffer = std::make_unique<Agate::FrameBufferUser>(1, 1);

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

    /**
     * @brief Applies the the current transform settings to the model
     */
    void ApplyTransform();
};

#endif // AGATE_EDITOR_GUI_LAYER_HPP
