#pragma once

#include "Core.h"
#include <spdlog/logger.h>

namespace Agate
{

    class API Logger {
    public:
        static void initLogger();
        static void printMSG(std::string msg, const char* file, const char* function, int line);
        static void printWarn(std::string msg, const char* file, const char* function, int line);
        static void printError(std::string msg, const char* file, const char* function, int line);
        static void printCrit(std::string msg, const char* file, const char* function, int line);

    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };
}// namespace Agate

//types of supported logging
#define PRINTMSG(x) Agate::Logger::printMSG(x, __FILE__, __func__, __LINE__);
#define PRINTWARN(x) Agate::Logger::printWarn(x, __FILE__, __func__, __LINE__);
#define PRINTERROR(x) Agate::Logger::printError(x, __FILE__, __func__, __LINE__);
#define PRINTCRIT(x) Agate::Logger::printCrit(x, __FILE__, __func__, __LINE__);
