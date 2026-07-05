#pragma once
#include <dpp/dpp.h>

class Bot;

namespace handlers {

void registerCommands(Bot& bot);
void handleSlashCommand(const dpp::interaction_create_t& event, Bot& bot);
void handlePrefixCommand(const dpp::message_create_t& event, Bot& bot);

}
