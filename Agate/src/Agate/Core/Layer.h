#pragma once

#include "Agate/Events/Event.h"

namespace Agate {
    class Layer {
    public:
        virtual void Attach() {}

        virtual void Detach() {}

        virtual void OnEvent(Event &e) {}

        virtual void OnRender() {};

    private:
        bool m_Enabled = true;
    };
}// namespace Agate
