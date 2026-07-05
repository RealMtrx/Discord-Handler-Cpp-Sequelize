#include "logger.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace handlers {

std::string Logger::timestamp() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string Logger::levelName(Level level) {
    switch (level) {
        case Info:  return "INFO";
        case Warn:  return "WARN";
        case Error: return "ERROR";
        case Debug: return "DEBUG";
        default:    return "UNKNOWN";
    }
}

void Logger::log(Level level, const std::string& message) {
    std::cout << "[" << timestamp() << "] [" << levelName(level) << "] " << message << std::endl;
}

void Logger::info(const std::string& message)  { log(Info, message); }
void Logger::warn(const std::string& message)  { log(Warn, message); }
void Logger::error(const std::string& message) { log(Error, message); }
void Logger::debug(const std::string& message) { log(Debug, message); }

}
