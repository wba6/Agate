#include "EntryPoint.h"
#include "Logger.h"
Agate::EntryPoint::EntryPoint()
{
}

Agate::EntryPoint::~EntryPoint()
{
}

void Agate::EntryPoint::Run()
{
    while (1) {
        PRINTWARN("Bacon");
    };
}
