
#include "Agate.h"

#include <iostream>
#include <string>
class app : public Agate::EntryPoint {

};

class layerEx : public Agate::Layer {

public:
    void Attach() override
    {
        PRINTMSG("ATTACHED")
    }

    void Detach() override
    {
    }

    void OnEvent(Agate::Event &e) override
    {
        //PRINTCRIT("REVEVED EVENT IN ONEVENT")
    }
};

Agate::EntryPoint *Agate::CreateEntryPoint()
{
    auto Application = new app();

    Application->EmplaceLayer(new layerEx);
    return Application;
}
