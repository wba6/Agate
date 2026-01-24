/**
 * @brief Include file for running an Agate executable. Defines main
 *        and utilizes `Agate::CreateEntryPoint` (which must be defined
 *        by consuming applications) to run Agate
 */

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
