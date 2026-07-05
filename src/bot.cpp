#include "bot.h"
#include "handlers/commands.h"
#include "events/ready.h"
#include "events/message_create.h"
#include "events/interaction_create.h"
#include "events/guild_create.h"
#include "events/guild_delete.h"

Bot::Bot(const Config& config)
    : config_(config)
    , cluster_(std::make_unique<dpp::cluster>(config_.token))
    , database_(std::make_unique<DatabaseConnection>(config_.dbStorage)) {}

void Bot::run() {
    database_->initialize();
    registerEvents();
    registerCommands();
    cluster_->start(dpp::st_wait);
}

void Bot::registerEvents() {
    OnReady(*cluster_);
    OnMessageCreate(*cluster_, *this);
    OnInteractionCreate(*cluster_, *this);
    OnGuildCreate(*cluster_);
    OnGuildDelete(*cluster_);
}

void Bot::registerCommands() {
    handlers::registerCommands(*this);
}

dpp::cluster& Bot::getCluster() { return *cluster_; }
DatabaseConnection& Bot::getDatabase() { return *database_; }
const Config& Bot::getConfig() const { return config_; }
