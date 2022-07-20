#pragma once

//-----------------------------------------Main Entry -----------------------------------
extern Agate::EntryPoint *Agate ::CreateEntryPoint();

int main()
{

    Agate::EntryPoint *application = Agate::CreateEntryPoint();
    application->Run();

    delete application;
    return 0;
}
//--------------------------------------------------------------------------------------
