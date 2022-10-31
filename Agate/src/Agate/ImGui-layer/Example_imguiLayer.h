//
// Created by William Aey on 8/31/2022.
//

#pragma once
#include "Layer.h"
namespace Agate
{
    class Example_imguiLayer : public Layer {
    public:
        Example_imguiLayer();

        virtual void Attach() override;
        virtual void Detach() override;
        virtual void OnEvent(Event &e) override;
        virtual void OnRender() override;


    private:
        bool m_Enabled = true;
    };
}// namespace Agate