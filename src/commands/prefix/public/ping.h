#pragma once
#include <dpp/dpp.h>
#include "bot.h"

namespace prefix {

inline void HandlePing(const dpp::message_create_t& event, Bot& bot) {
    dpp::message msg(event.msg.channel_id, "Pong!");
    bot.getCluster().message_create(msg);
}

}
