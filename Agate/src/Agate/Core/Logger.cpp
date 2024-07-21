#include "agpch.h"


#include "Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Agate
{
    std::shared_ptr<spdlog::logger> Logger::s_Logger;
    void Logger::printMSG(std::string msg, const char* file, const char* function, int line)
    {
        s_Logger->log(spdlog::source_loc{file, line, function}, spdlog::level::info, msg.c_str());
    }

    void Logger::printWarn(std::string msg, const char* file, const char* function, int line)
    {
        s_Logger->log(spdlog::source_loc{file, line, function}, spdlog::level::warn, msg.c_str());

    }

    void Logger::printError(std::string msg, const char* file, const char* function, int line)
    {
        s_Logger->log(spdlog::source_loc{file, line, function}, spdlog::level::err, msg.c_str());

    }

    void Logger::printCrit(std::string msg, const char* file, const char* function, int line)
    {
        s_Logger->log(spdlog::source_loc{file, line, function}, spdlog::level::critical, msg.c_str());
    }
    void Logger::initLogger()
    {
        try
        {
            s_Logger = spdlog::stdout_color_mt("Core");
            s_Logger->set_pattern("%^[%l][%n]%$[%H:%M:%S][%s][Line:%#] %v");
            s_Logger->set_level(spdlog::level::trace);
            s_Logger->critical("Logger initialization");
        }
        catch (const spdlog::spdlog_ex &ex)
        {
            std::cout << "Log initialization failed: " << ex.what() << std::endl;
        }
    }
}// namespace Agate
