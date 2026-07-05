#pragma once
#include <dpp/dpp.h>

class Bot;

namespace slash {

inline dpp::slashcommand PingCommand() {
    return dpp::slashcommand("ping", "Pong! Reply with latency", dpp::snowflake());
}

inline void HandlePing(const dpp::interaction_create_t& event, Bot& bot) {
    event.reply(dpp::interaction_response(
        dpp::ir_channel_message_with_source,
        dpp::message("Pong!")
    ));
}

}
