
#include "Agate.h"

#include <iostream>
#include <string>
class app : public Agate::EntryPoint {
};

int main()
{

    std::unique_ptr<app> App = std::make_unique<app>();
    App->Run();
    Agate::Vec2D vec2{50, 50};
    PRINTMSG(std::to_string((static_cast<int>(Agate::Magnitude(vec2)))));

    return 0;
}
