#pragma once
#include "Core.h"
#include "Events/ApplicationEvents.h"
#include "Events/Event.h"
#include "LayerStack.h"
#include "Window/Window.h"

namespace Agate
{
    class API EntryPoint {
    public:
        EntryPoint();
        virtual ~EntryPoint();

        void Run();

        void OnEvent(Event &e);
        bool OnWindowClose(WindowCloseEvent &e);

        void EmplaceLayer(Layer *layer);
        void RemoveLayer(Layer *layer);
        void EmplaceOverlay(Layer *overlay);
        void RemoveOverlay(Layer *overlay);

        static EntryPoint *&GetInstance();

    private:
        std::shared_ptr<Window> m_window;
        LayerStack m_layerStack;
        bool m_running;

    private:
        static EntryPoint *s_instance;
    };

    //to be defined outside of lib
    EntryPoint *CreateEntryPoint();

}// namespace Agate
