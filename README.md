<div align="center">
  <h1>Discord Handler — C++ (SQL Edition)</h1>
  <p><strong>A production-ready Discord bot framework built with DPP (Discord++) and sqlpp11 — supports SQLite with a modular src/ architecture.</strong></p>

  <p>
    <a href="https://github.com/RealMtrx/Discord-Handler-Cpp-Sequelize/blob/main/LICENSE"><img src="https://img.shields.io/badge/license-MIT-blue.svg" alt="License"></a>
    <a href="https://github.com/RealMtrx/Discord-Handler-Cpp-Sequelize/releases"><img src="https://img.shields.io/badge/version-0.9.0--beta-yellow" alt="Version 0.9.0 Beta"></a>
    <a href="https://github.com/RealMtrx/Discord-Handler-Cpp-Sequelize/stargazers"><img src="https://img.shields.io/github/stars/RealMtrx/Discord-Handler-Cpp-Sequelize" alt="Stars"></a>
    <a href="https://github.com/RealMtrx/Discord-Handler-Cpp-Sequelize/issues"><img src="https://img.shields.io/github/issues/RealMtrx/Discord-Handler-Cpp-Sequelize" alt="Issues"></a>
    <a href="https://github.com/RealMtrx/Discord-Handler-Cpp-Sequelize/network"><img src="https://img.shields.io/github/forks/RealMtrx/Discord-Handler-Cpp-Sequelize" alt="Forks"></a>
    <a href="https://github.com/RealMtrx/Discord-Handler/graphs/contributors"><img src="https://img.shields.io/badge/ecosystem-26%20repos-brightgreen" alt="26 Repos"></a>
    <a href="https://discord.gg/0hu2"><img src="https://img.shields.io/badge/discord-0hu2-5865F2" alt="Discord"></a>
  </p>

  <br>

  <p>
    <a href="#-features">Features</a> •
    <a href="#-quick-start">Quick Start</a> •
    <a href="#-project-structure">Structure</a> •
    <a href="#-database-configuration">Database Config</a> •
    <a href="#-api-reference">API</a> •
    <a href="#-mongodb-edition">MongoDB Edition</a> •
    <a href="#-related-repositories">Ecosystem</a>
  </p>
</div>

---

## Overview

Discord Handler C++ (SQL Edition) is the **C++ Sequelize variant** of the multi-language Discord Handler ecosystem. Built on **DPP (Discord++)** with **sqlpp11**, it provides a high-performance, event-driven foundation for Discord bots with dual command support (slash + prefix), SQLite database persistence via type-safe SQL queries, webhook-based logging, and an anti-crash layer.

The entry point (`main.cpp`) boots in a predictable sequence: initialize the anti-crash handler, open the SQLite database via sqlpp11, load slash commands, prefix commands, events, and core utilities, and finally log in via `dpp::cluster`.

## Features

- **Dual Command System** — Slash commands via DPP's `on_slashcommand` and prefix commands via `on_message_create`
- **Modular Architecture** — Separated concerns across `core/`, `database/`, `events/`, `handlers/`, `models/`, and `commands/`
- **C++17** — Built on modern C++ with `std::optional`, `std::variant`, and structured bindings
- **Anti-Crash** — Global `std::set_terminate` and signal handler interception via `handlers/anticrash.cpp`
- **Webhook Logging** — Webhook utilities via `core/webhooks.cpp`
- **sqlpp11 ORM** — Compile-time type-safe SQL queries with sqlpp11-sqlite3 connector
- **Cooldown System** — Per-command cooldown tracked in `core/cooldown.cpp`
- **Environment Configuration** — Token and database settings via `.env` in `config.cpp`
- **CMake Build** — Cross-platform build system via CMake >= 3.16

## Quick Start

```bash
git clone https://github.com/RealMtrx/Discord-Handler-Cpp-Sequelize.git
cd Discord-Handler-Cpp-Sequelize
```

**Requirements:** CMake >= 3.16, C++17 compiler, DPP, sqlpp11, sqlpp11-sqlite3.

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

Copy `.env.example` to `.env` and fill in your values:

```env
TOKEN=your_bot_token_here
CLIENT_ID=your_client_id_here
GUILD_ID=your_guild_id_here
DB_DIALECT=sqlite
DB_STORAGE=database.sqlite
```

```bash
./build/Discord-Handler-Cpp-Sequelize
```

### Dependencies

| Library | Version | Purpose |
|---------|---------|---------|
| [DPP](https://github.com/brainboxdotcc/DPP) | 10.x | Discord C++ library |
| [sqlpp11](https://github.com/rbock/sqlpp11) | 0.63 | Type-safe SQL ORM |
| [sqlpp11-sqlite3](https://github.com/rbock/sqlpp11-sqlite3) | 0.63 | SQLite3 connector |
| nlohmann/json | 3.x | JSON parsing (via DPP) |

## Project Structure

```
Discord-Handler-Cpp-Sequelize/
├── CMakeLists.txt                 # CMake build configuration
├── src/
│   ├── main.cpp                   # Entry point — boot sequence
│   ├── config.h / config.cpp      # Bot configuration (token, prefixes, webhooks)
│   ├── bot.h / bot.cpp            # Bot initialization and client setup
│   ├── core/
│   │   ├── webhooks.h / webhooks.cpp  # Webhook utility
│   │   └── cooldown.h / cooldown.cpp  # Cooldown system
│   ├── database/
│   │   └── connection.h / connection.cpp  # sqlpp11 database setup
│   ├── events/
│   │   └── *.h / *.cpp            # Discord event handlers
│   ├── handlers/
│   │   ├── anticrash.h / anticrash.cpp  # Global error interception
│   │   ├── commands.h / commands.cpp    # Command routing
│   │   └── logger.h / logger.cpp        # Logger for bot activity
│   ├── models/
│   │   └── User.h                 # User data model (sqlpp11 table)
│   └── commands/
│       ├── prefix/                # Prefix command implementations
│       └── slash/                 # Slash command implementations
```

## Database Configuration

Set `DB_DIALECT` to `sqlite` and configure `DB_STORAGE` as the file path:

```env
DB_DIALECT=sqlite
DB_STORAGE=database.sqlite
```

The `database/connection.cpp` file initializes the sqlpp11 database connection:

```cpp
#include <sqlpp11/sqlite3/connection.h>
#include <sqlpp11/sqlpp11.h>

namespace db {
    sqlpp::sqlite3::connection_config config;
    config.path_to_database = Config::get("DB_STORAGE");
    config.flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;

    sqlpp::sqlite3::connection connection(config);

    // Create tables if not exist
    connection.execute(R"(
        CREATE TABLE IF NOT EXISTS users (
            id TEXT PRIMARY KEY,
            username TEXT NOT NULL,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP
        )
    )");
}
```

sqlpp11 provides compile-time type safety for SQL queries, preventing malformed queries at build time rather than runtime.

## API Reference

### Entry Point — `src/main.cpp`

```cpp
int main(int argc, char* argv[])
```

Creates a `dpp::cluster` with the bot token. Registers handlers: `on_log`, `on_ready`, `on_slashcommand`, `on_message_create`, `on_guild_create`, `on_guild_delete`. Loads the database connection, registers commands, and starts the cluster via `cluster.start(false)`.

### Configuration — `src/config.cpp`

| Key | Type | Description |
|-----|------|-------------|
| `TOKEN` | `std::string` | Discord bot token |
| `CLIENT_ID` | `std::string` | Discord application client ID |
| `GUILD_ID` | `std::string` | Guild ID for guild-specific commands |
| `DB_DIALECT` | `std::string` | Database dialect (currently `sqlite`) |
| `DB_STORAGE` | `std::string` | SQLite database file path |

### Handlers

- **AntiCrash** — Registers `std::set_terminate` and signal handlers (`SIGSEGV`, `SIGABRT`, `SIGFPE`, `SIGILL`) for global exception/signal interception
- **Commands** — Routes slash commands via DPP's `on_slashcommand` and prefix commands via `on_message_create`
- **Logger** — Writes a startup report with command/event counts and database status

### Core Utilities

- **Cooldown** — `checkCooldown(name, userId)` returns remaining milliseconds or 0 if not on cooldown
- **Webhooks** — `sendWebhook(url, message)` utility for Discord webhook integration

## Adding Commands

### Slash Command

Create `src/commands/slash/[name].h` / `src/commands/slash/[name].cpp`:

```cpp
// ping.h
#pragma once
#include <dpp/dpp.h>

void register_ping_command(dpp::cluster& bot);

// ping.cpp
#include "ping.h"

void register_ping_command(dpp::cluster& bot) {
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong! 🏓");
        }
    });
}
```

### Prefix Command

Prefix commands are handled via `on_message_create` in the commands handler:

```cpp
bot.on_message_create([&](const dpp::message_create_t& event) {
    std::string msg = event.msg.content;
    if (msg.rfind(prefix, 0) == 0) {
        std::string cmd = msg.substr(prefix.length());
        if (cmd == "ping") {
            event.reply("Pong! 🏓");
        }
    }
});
```

New commands are added by registering them in the command setup function. No manual wiring is needed beyond adding the handler.

## MongoDB Edition

A **MongoDB** variant of this handler is available for teams that prefer a document database:

[RealMtrx/Discord-Handler-Cpp](https://github.com/RealMtrx/Discord-Handler-Cpp)

It replaces `database/connection.cpp` with a MongoDB driver connection (via `mongocxx`) and swaps sqlpp11 table definitions for BSON documents. All other modules — events, commands, handlers, core utilities — remain identical.

## Related Repositories

The Discord Handler ecosystem spans **26 repositories** across 13 languages, each available in both MongoDB and Sequelize editions.

### Base Repositories (MongoDB)

| Language | Repository |
|----------|------------|
| C++ | [RealMtrx/Discord-Handler-Cpp](https://github.com/RealMtrx/Discord-Handler-Cpp) |
| C# | [RealMtrx/Discord-Handler-Cs](https://github.com/RealMtrx/Discord-Handler-Cs) |
| Dart | [RealMtrx/Discord-Handler-Dart](https://github.com/RealMtrx/Discord-Handler-Dart) |
| Go | [RealMtrx/Discord-Handler-Go](https://github.com/RealMtrx/Discord-Handler-Go) |
| Java | [RealMtrx/Discord-Handler-Java](https://github.com/RealMtrx/Discord-Handler-Java) |
| JavaScript | [RealMtrx/Discord-Handler-Js](https://github.com/RealMtrx/Discord-Handler-Js) |
| Kotlin | [RealMtrx/Discord-Handler-Kt](https://github.com/RealMtrx/Discord-Handler-Kt) |
| Lua | [RealMtrx/Discord-Handler-Lua](https://github.com/RealMtrx/Discord-Handler-Lua) |
| PHP | [RealMtrx/Discord-Handler-Php](https://github.com/RealMtrx/Discord-Handler-Php) |
| Python | [RealMtrx/Discord-Handler-Py](https://github.com/RealMtrx/Discord-Handler-Py) |
| Ruby | [RealMtrx/Discord-Handler-Rb](https://github.com/RealMtrx/Discord-Handler-Rb) |
| Rust | [RealMtrx/Discord-Handler-Rs](https://github.com/RealMtrx/Discord-Handler-Rs) |
| TypeScript | [RealMtrx/Discord-Handler](https://github.com/RealMtrx/Discord-Handler) ← hub |

### Sequelize (SQL) Editions

| Language | Repository |
|----------|------------|
| C++ | [RealMtrx/Discord-Handler-Cpp-Sequelize](https://github.com/RealMtrx/Discord-Handler-Cpp-Sequelize) |
| C# | [RealMtrx/Discord-Handler-Cs-Sequelize](https://github.com/RealMtrx/Discord-Handler-Cs-Sequelize) |
| Dart | [RealMtrx/Discord-Handler-Dart-Sequelize](https://github.com/RealMtrx/Discord-Handler-Dart-Sequelize) |
| Go | [RealMtrx/Discord-Handler-Go-Sequelize](https://github.com/RealMtrx/Discord-Handler-Go-Sequelize) |
| Java | [RealMtrx/Discord-Handler-Java-Sequelize](https://github.com/RealMtrx/Discord-Handler-Java-Sequelize) |
| JavaScript | [RealMtrx/Discord-Handler-Js-Sequelize](https://github.com/RealMtrx/Discord-Handler-Js-Sequelize) |
| Kotlin | [RealMtrx/Discord-Handler-Kt-Sequelize](https://github.com/RealMtrx/Discord-Handler-Kt-Sequelize) |
| Lua | [RealMtrx/Discord-Handler-Lua-Sequelize](https://github.com/RealMtrx/Discord-Handler-Lua-Sequelize) |
| PHP | [RealMtrx/Discord-Handler-Php-Sequelize](https://github.com/RealMtrx/Discord-Handler-Php-Sequelize) |
| Python | [RealMtrx/Discord-Handler-Py-Sequelize](https://github.com/RealMtrx/Discord-Handler-Py-Sequelize) |
| Ruby | [RealMtrx/Discord-Handler-Rb-Sequelize](https://github.com/RealMtrx/Discord-Handler-Rb-Sequelize) |
| Rust | [RealMtrx/Discord-Handler-Rs-Sequelize](https://github.com/RealMtrx/Discord-Handler-Rs-Sequelize) |
| TypeScript | [RealMtrx/Discord-Handler-Ts-Sequelize](https://github.com/RealMtrx/Discord-Handler-Ts-Sequelize) |

> **[RealMtrx/Discord-Handler](https://github.com/RealMtrx/Discord-Handler)** — the TypeScript hub and flagship repository. Star it to support the ecosystem.

## License

Distributed under the MIT License. See `LICENSE` for more information.

---

Built by **Mtrx** — Discord: **0hu2** — [RealMtrx/Discord-Handler](https://github.com/RealMtrx/Discord-Handler)
