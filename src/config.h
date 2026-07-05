#pragma once
#include <string>

struct Config {
    std::string token;
    std::string clientId;
    std::string guildId;
    std::string dbDialect;
    std::string dbStorage;

    static Config load();
};
