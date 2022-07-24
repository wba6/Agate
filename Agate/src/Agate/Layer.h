#pragma once

namespace Agate
{
    class Layer {
    public:
        virtual void Attach() {}
        virtual void Detach() {}
        virtual void OnEvent() {}

    private:
        bool m_Enabled;
    };
}// namespace Agate
