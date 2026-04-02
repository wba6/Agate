/**
 * @brief GUI editor for the Agate engine
 */

#include "Agate.h"

class Editor : public Agate::EntryPoint {};

Agate::EntryPoint* Agate::CreateEntryPoint() {
    return new Editor();
}
