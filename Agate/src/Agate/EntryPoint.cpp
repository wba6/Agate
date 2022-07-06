#include "EntryPoint.h"
#include "Logger.h"
#include "../Events/MouseEvent.h"
#include "../Events/Event.h"

Agate::EntryPoint::EntryPoint()
{
}

Agate::EntryPoint::~EntryPoint()
{
}

void Agate::EntryPoint::Run()
{
    auto click = MouseClick();
    auto search = EventClassifier(click);

    while (1) {
        PRINTWARN("Bacon");
    };

}
