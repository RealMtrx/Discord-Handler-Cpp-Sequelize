#pragma once
#include <dpp/dpp.h>
#include "bot.h"
#include "handlers/commands.h"

inline void OnInteractionCreate(dpp::cluster& client, Bot& bot) {
    client.on_interaction_create([&bot](const dpp::interaction_create_t& event) {
        if (event.command.type == dpp::it_application_command) {
            handlers::handleSlashCommand(event, bot);
        }
    });
}
