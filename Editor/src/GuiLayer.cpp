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
