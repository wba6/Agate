
#include "Agate.h"

#include <iostream>
#include <string>
class app : public Agate::EntryPoint {

public:
};

class layerEx : public Agate::Layer {

public:
    void Attach() override
    {
        PRINTCRIT("ATTACHED")
    }

    void Detach() override
    {
    }

    void OnEvent(Agate::Event &e) override
    {
        PRINTCRIT("REVEVED EVENT IN ONEVENT")
    }
};

Agate::EntryPoint *Agate::CreateEntryPoint()
{
    return new app();
}
