//
// Created by TANK1_41 on 9/21/2022.
//

#pragma once
#include "Context.h"
namespace Agate
{


    class CurrentContext {
    public:
        CurrentContext() = delete;
        static bool OpenGL;
        static Context *&GetCurrentContex();
        static void SetContextPointer(Context *ptr);

    private:
        static Context *CurrentContextPointer;
    };
}// namespace Agate