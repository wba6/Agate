#pragma once

#include "Agate/Events/ApplicationEvents.h"
#include "Agate/Events/Event.h"
#include "Agate/Window/Window.h"
#include "Core.h"
#include "LayerStack.h"

namespace Agate {
    class API EntryPoint {
    public:
        EntryPoint();

        virtual ~EntryPoint();

        void Run();

        void OnEvent(Event &e);

        bool OnWindowClose(WindowCloseEvent &e);

        void EmplaceLayer(std::shared_ptr<Layer> layer);

        void RemoveLayer(std::shared_ptr<Layer> layer);

        void EmplaceOverlay(std::shared_ptr<Layer> overlay);

        void RemoveOverlay(std::shared_ptr<Layer> overlay);

        float GetDeltaTime();

        std::shared_ptr<Agate::Window> GetWindow();

        static EntryPoint *&GetInstance();

    private:
        std::shared_ptr<Window> m_window;
        LayerStack m_layerStack;
        bool m_running;
        float deltaTime;

    private:
        static EntryPoint *s_instance;
    };

    //to be defined outside of lib
    EntryPoint *CreateEntryPoint();

}// namespace Agate
