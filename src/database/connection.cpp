#include "connection.h"
#include <iostream>

DatabaseConnection::DatabaseConnection(const std::string& storage) {
    auto config = std::make_shared<sqlpp::sqlite3::connection_config>();
    config->path_to_database = storage;
    config->flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
    connection_ = std::make_shared<sqlpp::sqlite3::connection>(config);
}

sqlpp::sqlite3::connection& DatabaseConnection::get() {
    return *connection_;
}

void DatabaseConnection::initialize() {
    connection_->execute(R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            discord_id TEXT NOT NULL UNIQUE,
            username TEXT,
            discriminator TEXT,
            created_at TEXT DEFAULT (datetime('now'))
        )
    )");
    std::cout << "[Database] Tables initialized" << std::endl;
}
