#include "agpch.h"


#include "Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Agate {
    std::shared_ptr<spdlog::logger> Logger::s_Logger;

    void Logger::initLogger() {
        try {
            s_Logger = spdlog::stdout_color_mt("Core");
            s_Logger->set_pattern("%^[%l][%n]%$[%H:%M:%S][%s][Line:%#] %v");
            s_Logger->set_level(spdlog::level::trace);
            PRINTCRIT("Logger initialization");
        }
        catch (const spdlog::spdlog_ex &ex) {
            std::cout << "Log initialization failed: " << ex.what() << std::endl;
        }
    }
}// namespace Agate
