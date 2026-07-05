#pragma once
#include <dpp/dpp.h>
#include "bot.h"
#include "handlers/commands.h"

inline void OnMessageCreate(dpp::cluster& client, Bot& bot) {
    client.on_message_create([&bot](const dpp::message_create_t& event) {
        if (event.msg.author.is_bot()) return;
        handlers::handlePrefixCommand(event, bot);
    });
}
