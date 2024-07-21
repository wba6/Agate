#pragma once

//-----------------------------------------Main Entry -----------------------------------
extern Agate::EntryPoint *Agate::CreateEntryPoint();

int main() {
    Agate::Logger::initLogger();

    Agate::EntryPoint *application = Agate::CreateEntryPoint();
    application->Run();

    delete application;
    return 0;
}
//--------------------------------------------------------------------------------------
