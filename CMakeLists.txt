cmake_minimum_required(VERSION 3.16)
project(Discord-Handler-Cpp-Sequelize VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(dpp REQUIRED)
find_package(sqlpp11 REQUIRED)
find_package(sqlpp11-sqlite3 REQUIRED)

set(SOURCES
    src/main.cpp
    src/config.cpp
    src/bot.cpp
    src/database/connection.cpp
    src/handlers/anticrash.cpp
    src/handlers/commands.cpp
    src/handlers/logger.cpp
    src/core/webhooks.cpp
    src/core/cooldown.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        dpp::dpp
        sqlpp11::sqlpp11
        sqlpp11::sqlite3
)
