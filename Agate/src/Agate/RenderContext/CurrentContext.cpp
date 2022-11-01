//
// Created by TANK1_41 on 9/21/2022.
//
#include "CurrentContext.h"
#include "Agate/Core/Logger.h"

bool Agate::CurrentContext::OpenGL = false;
Agate::Context *Agate::CurrentContext::CurrentContextPointer = nullptr;
Agate::Context *&Agate::CurrentContext::GetCurrentContex()
{
    if (CurrentContextPointer == nullptr)
        PRINTCRIT("Context Pointer Requested before initialized");
    return CurrentContextPointer;
}
void Agate::CurrentContext::SetContextPointer(Context *ptr)
{
    CurrentContextPointer = ptr;
}
