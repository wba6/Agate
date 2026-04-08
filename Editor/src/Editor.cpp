/**
 * @brief GUI editor for the Agate engine
 */

#include "Agate.h"
#include "GuiLayer.hpp"

class Editor : public Agate::EntryPoint {};

Agate::EntryPoint* Agate::CreateEntryPoint() {

    Editor* editor = new Editor();
    editor->EmplaceOverlay(std::make_shared<GuiLayer>(editor->GetWindow()));

    return editor;
}
