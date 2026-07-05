#pragma once
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/sqlite3/sqlite3.h>
#include <memory>
#include <string>

class DatabaseConnection {
public:
    explicit DatabaseConnection(const std::string& storage);
    sqlpp::sqlite3::connection& get();
    void initialize();

private:
    std::shared_ptr<sqlpp::sqlite3::connection> connection_;
};
