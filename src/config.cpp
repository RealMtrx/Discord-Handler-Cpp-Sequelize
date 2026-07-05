#include "config.h"
#include <fstream>
#include <algorithm>
#include <cctype>
#include <cstdlib>

static std::string trim(const std::string& s) {
    auto front = std::find_if_not(s.begin(), s.end(),
        [](unsigned char c) { return std::isspace(c); });
    auto back = std::find_if_not(s.rbegin(), s.rend(),
        [](unsigned char c) { return std::isspace(c); }).base();
    return (front < back) ? std::string(front, back) : "";
}

static std::string unquote(const std::string& s) {
    if (s.size() >= 2) {
        char q = s.front();
        if ((q == '"' || q == '\'') && s.back() == q)
            return s.substr(1, s.size() - 2);
    }
    return s;
}

Config Config::load() {
    Config cfg;
    cfg.dbDialect = "sqlite";
    cfg.dbStorage = "database.sqlite";

    std::ifstream file(".env");
    if (!file.is_open()) {
        const char* val;
        if ((val = std::getenv("TOKEN")))       cfg.token = val;
        if ((val = std::getenv("CLIENT_ID")))   cfg.clientId = val;
        if ((val = std::getenv("GUILD_ID")))    cfg.guildId = val;
        if ((val = std::getenv("DB_DIALECT")))  cfg.dbDialect = val;
        if ((val = std::getenv("DB_STORAGE")))  cfg.dbStorage = val;
        return cfg;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        auto eq = line.find('=');
        if (eq == std::string::npos) continue;
        std::string key = trim(line.substr(0, eq));
        std::string value = unquote(trim(line.substr(eq + 1)));

        if (key == "TOKEN")         cfg.token = value;
        else if (key == "CLIENT_ID") cfg.clientId = value;
        else if (key == "GUILD_ID") cfg.guildId = value;
        else if (key == "DB_DIALECT") cfg.dbDialect = value;
        else if (key == "DB_STORAGE") cfg.dbStorage = value;
    }
    return cfg;
}
