#pragma once

#include "Core.h"
#include <spdlog/logger.h>

namespace Agate
{

    class API Logger {
    public:
        static void initLogger();

        template<typename... Args>
        static void printMSG(const char* file, const char* function, int line, const char* format, Args&&... args)
        {
            s_Logger->log(spdlog::source_loc{file, line, function}, spdlog::level::info, fmt::format(format, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void printWarn(const char* file, const char* function, int line, const char* format, Args&&... args) {
            s_Logger->log(spdlog::source_loc{file, line, function}, spdlog::level::info, fmt::format(format, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void printError(const char* file, const char* function, int line, const char* format, Args&&... args) {
            s_Logger->log(spdlog::source_loc{file, line, function}, spdlog::level::info, fmt::format(format, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void printCrit(const char* file, const char* function, int line, const char* format, Args&&... args) {
            s_Logger->log(spdlog::source_loc{file, line, function}, spdlog::level::info, fmt::format(format, std::forward<Args>(args)...));
        }

    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };
}// namespace Agate

//types of supported logging
#define PRINTMSG(format, ...) Agate::Logger::printMSG(__FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
#define PRINTWARN(format, ...) Agate::Logger::printWarn(__FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
#define PRINTERROR(format, ...) Agate::Logger::printError(__FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
#define PRINTCRIT(format, ...) Agate::Logger::printCrit(__FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
