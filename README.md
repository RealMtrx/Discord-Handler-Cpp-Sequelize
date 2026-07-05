# Discord-Handler-Cpp-Sequelize

A Discord bot in C++ using DPP (Discord++) library and sqlpp11 ORM.

## Features

- Slash and prefix command handling
- SQLite database via sqlpp11 ORM
- Event-driven architecture
- Cooldown system
- Webhook utilities
- Crash/exception handling

## Requirements

- CMake >= 3.16
- C++17 compatible compiler
- [dpp](https://github.com/brainboxdotcc/DPP) - Discord C++ library
- [sqlpp11](https://github.com/rbock/sqlpp11) - SQL type-safe ORM
- [sqlpp11-sqlite3](https://github.com/rbock/sqlpp11-sqlite3) - SQLite3 connector

## Build

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

## Configuration

Copy `.env.example` to `.env` and fill in your values:

```
TOKEN=your_bot_token_here
CLIENT_ID=your_client_id_here
GUILD_ID=your_guild_id_here
DB_DIALECT=sqlite
DB_STORAGE=database.sqlite
```

## Run

```bash
./build/Discord-Handler-Cpp-Sequelize
```
