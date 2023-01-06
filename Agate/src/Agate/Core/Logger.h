#pragma once

#include "Core.h"
#include "spdlog/logger.h"

namespace Agate
{

    class API Logger {
    public:
        static void initLogger();
        static void printMSG(std::string msg);
        static void printWarn(std::string msg);
        static void printError(std::string msg);
        static void printCrit(std::string msg);

    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };
}// namespace Agate

#define PRINTMSG(x) Agate::Logger::printMSG(x);
#define PRINTWARN(x) Agate::Logger::printWarn(x);
#define PRINTERROR(x) Agate::Logger::printError(x);
#define PRINTCRIT(x) Agate::Logger::printCrit(x);
