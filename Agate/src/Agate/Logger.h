#pragma once
#include <string>
#include "Core.h"

namespace Agate
{

    class API Logger {
    public:
        static void printMSG(std::string msg);
        static void printWarn(std::string msg);
        static void printCrit(std::string msg);
    };
}

#define PRINTMSG(x) Logger::printMSG(x);
#define PRINTWARN(x) Logger::printWarn(x);
#define PRINTCRIT(x) Logger::printCrit(x);
