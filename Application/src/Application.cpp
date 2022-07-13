
#include "Agate.h"


class app : public Agate::EntryPoint {
};

int main()
{

    Agate::helloWorld();
    std::unique_ptr<app> App = std::make_unique<app>();
    App->Run();

    return 0;
}
