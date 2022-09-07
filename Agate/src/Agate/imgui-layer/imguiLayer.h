//
// Created by William Aey on 8/31/2022.
//

#pragma once
#include "Layer.h"
namespace Agate
{
    class imguiLayer : public Layer {
    public:
        imguiLayer(void *GlfwWindow);
        virtual void Attach() override;
        virtual void Detach() override;
        virtual void OnEvent(Event &e) override;
        virtual void onRender() override;
        static void Begin();
        static void End();

    private:
        void* m_glfwWindow;
        bool m_Enabled = true;
    };
}// namespace Agate