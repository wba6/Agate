#pragma once

#include "Core.h"
#include <spdlog/logger.h>

namespace Agate {

    /**
     * @brief Adapter to decouple internal logging from spdlog
     */
    class Logger {
    public:

        /**
         * @brief Initializes logging format
         */
        static void initLogger();

        /**
         * @brief Logs a message at the info level. For informational messages
         *        that do not indicate any issue
         * 
         * @param file Name of the file creating the log
         * @param function Name of the function creating the log
         * @param line Source code line creating the log
         * @param format Message to log. Supports a base format string
         * @param args If using a format string, the content to populate format
         *             markers
         */
        template<typename... Args>
        static void printMSG(const char *file, const char *function, int line, const char *format, Args &&... args) {
            s_Logger->log(spdlog::source_loc{file, line, function}, spdlog::level::info,
                          fmt::format(format, std::forward<Args>(args)...));
        }

        /**
         * @brief Logs a message at the warn level. For warnings that are
         *        unlikely to cause a non-recoverable error
         * 
         * @param file Name of the file creating the log
         * @param function Name of the function creating the log
         * @param line Source code line creating the log
         * @param format Message to log. Supports a base format string
         * @param args If using a format string, the content to populate format
         *             markers
         */
        template<typename... Args>
        static void printWarn(const char *file, const char *function, int line, const char *format, Args &&... args) {
            s_Logger->log(spdlog::source_loc{file, line, function}, spdlog::level::warn,
                          fmt::format(format, std::forward<Args>(args)...));
        }

        /**
         * @brief Logs a message at the info level. For warnings that the
         *        state of the program is knowingly susceptible to a non-recoverable
         *        error
         * 
         * @param file Name of the file creating the log
         * @param function Name of the function creating the log
         * @param line Source code line creating the log
         * @param format Message to log. Supports a base format string
         * @param args If using a format string, the content to populate format
         *             markers
         */
        template<typename... Args>
        static void printError(const char *file, const char *function, int line, const char *format, Args &&... args) {
            s_Logger->log(spdlog::source_loc{file, line, function}, spdlog::level::err,
                          fmt::format(format, std::forward<Args>(args)...));
        }

        /**
         * @brief Logs a message at the info level. For non-recoverable errors
         * 
         * @param file Name of the file creating the log
         * @param function Name of the function creating the log
         * @param line Source code line creating the log
         * @param format Message to log. Supports a base format string
         * @param args If using a format string, the content to populate format
         *             markers
         */
        template<typename... Args>
        static void printCrit(const char *file, const char *function, int line, const char *format, Args &&... args) {
            s_Logger->log(spdlog::source_loc{file, line, function}, spdlog::level::critical,
                          fmt::format(format, std::forward<Args>(args)...));
        }

    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };
}// namespace Agate

/**
 * @brief Logs a message at the info level. For informational messages
 *        that do not indicate any issue
 * 
 * @param format Message to log. Supports a base format string
 * @param args If using a format string, the content to populate format
 *             markers
 */
#define PRINTMSG(format, ...) Agate::Logger::printMSG(__FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
/**
 * @brief Logs a message at the warn level. For warnings that are
 *        unlikely to cause a non-recoverable error
 * 
 * @param format Message to log. Supports a base format string
 * @param args If using a format string, the content to populate format
 *             markers
 */
#define PRINTWARN(format, ...) Agate::Logger::printWarn(__FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
/**
 * @brief Logs a message at the info level. For warnings that the
 *        state of the program is knowingly susceptible to a non-recoverable
 *        error
 * 
 * @param format Message to log. Supports a base format string
 * @param args If using a format string, the content to populate format
 *             markers
 */
#define PRINTERROR(format, ...) Agate::Logger::printError(__FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
/**
 * @brief Logs a message at the info level. For non-recoverable errors
 * 
 * @param format Message to log. Supports a base format string
 * @param args If using a format string, the content to populate format
 *             markers
 */
#define PRINTCRIT(format, ...) Agate::Logger::printCrit(__FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
