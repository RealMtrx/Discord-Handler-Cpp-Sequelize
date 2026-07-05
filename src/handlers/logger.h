#pragma once
#include <string>

namespace handlers {

class Logger {
public:
    enum Level { Info, Warn, Error, Debug };

    static void log(Level level, const std::string& message);
    static void info(const std::string& message);
    static void warn(const std::string& message);
    static void error(const std::string& message);
    static void debug(const std::string& message);

private:
    static std::string timestamp();
    static std::string levelName(Level level);
};

}
