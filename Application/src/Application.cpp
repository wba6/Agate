
#include "Agate.h"

#include <iostream>
#include <string>
class app : public Agate::EntryPoint {

public:
    virtual void Run()
    {
        Agate::Vec2D vec2{50, 50};
        PRINTMSG(std::to_string((static_cast<int>(Agate::Magnitude(vec2)))));

        EntryPoint::Run();
    }
};

int main()
{

    std::unique_ptr<app> App = std::make_unique<app>();
    App->Run();
    Agate::Vec2D vec2{50, 50};
    PRINTMSG(std::to_string((static_cast<int>(Agate::Magnitude(vec2)))));

    return 0;
}

Agate::EntryPoint *Agate::CreateEntryPoint()
{
    return new app();
}
