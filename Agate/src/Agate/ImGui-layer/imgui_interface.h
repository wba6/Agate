//
// Created by TANK1_41 on 10/31/2022.
//

#ifndef AGATE_IMGUI_INTERFACE_H
#define AGATE_IMGUI_INTERFACE_H

namespace Agate {
    class imgui_interface {

    public:
        static void Init(void *window);

        static void ImguiDestruct();

        static void BeginFrame();

        static void EndFrame();

    private:
        imgui_interface() {};
    };

}// namespace Agate
#endif//AGATE_IMGUI_INTERFACE_H
