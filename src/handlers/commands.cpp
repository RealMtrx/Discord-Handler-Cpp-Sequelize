#include "commands.h"
#include "bot.h"
#include "commands/slash/public/ping.h"
#include "commands/prefix/public/ping.h"

namespace handlers {

void registerCommands(Bot& bot) {
    auto& cluster = bot.getCluster();
    dpp::slashcommand cmd = slash::PingCommand();

    if (bot.getConfig().guildId.empty()) {
        cluster.global_command_create(cmd);
    } else {
        cluster.guild_command_create(cmd, bot.getConfig().guildId);
    }
}

void handleSlashCommand(const dpp::interaction_create_t& event, Bot& bot) {
    std::string name = event.command.get_command_name();
    if (name == "ping") {
        slash::HandlePing(event, bot);
    }
}

void handlePrefixCommand(const dpp::message_create_t& event, Bot& bot) {
    const std::string& msg = event.msg.content;
    if (msg.rfind("!ping", 0) == 0) {
        prefix::HandlePing(event, bot);
    }
}

}
