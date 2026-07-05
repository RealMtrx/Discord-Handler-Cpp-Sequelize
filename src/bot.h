#pragma once
#include <dpp/dpp.h>
#include <memory>
#include "config.h"
#include "database/connection.h"

class Bot {
public:
    explicit Bot(const Config& config);
    ~Bot() = default;
    Bot(const Bot&) = delete;
    Bot& operator=(const Bot&) = delete;

    void run();
    dpp::cluster& getCluster();
    DatabaseConnection& getDatabase();
    const Config& getConfig() const;

private:
    Config config_;
    std::unique_ptr<dpp::cluster> cluster_;
    std::unique_ptr<DatabaseConnection> database_;

    void registerEvents();
    void registerCommands();
};
