#pragma once
#include "Events/Event.h"

namespace Agate
{
    class Layer {
    public:
        virtual void Attach() {}
        virtual void Detach() {}
        virtual void OnEvent(Event &e) {}
        virtual void onRender() {};
    private:
        bool m_Enabled = true;
    };
}// namespace Agate
