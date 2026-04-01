#include "Main.h"
#include "Async/TaskPool.h"
#include "EntryPoint.h"
#include "Logger.h"

extern Agate::EntryPoint *Agate::CreateEntryPoint();

int main() {
    Agate::Logger::initLogger();
    Agate::TaskPool::Initialize();

    Agate::EntryPoint *application = Agate::CreateEntryPoint();
    application->Run();

    delete application;
    return 0;
}
