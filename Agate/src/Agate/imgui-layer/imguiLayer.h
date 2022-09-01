//
// Created by William Aey on 8/31/2022.
//

#pragma once
#include "Layer.h"
namespace Agate
{
    class imguiLayer : public Layer {
    public:
        virtual void Attach() {}
        virtual void Detach() {}
        virtual void OnEvent(Event &e) {}

    private:
        bool m_Enabled = true;
    };
}// namespace Agate