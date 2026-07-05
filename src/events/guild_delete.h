#pragma once
#include <dpp/dpp.h>

inline void OnGuildDelete(dpp::cluster& client) {
    client.on_guild_delete([](const dpp::guild_delete_t& event) {
        dpp::log(dpp::loglevel::ll_debug,
            "Removed from guild: " + std::to_string(event.guild_id));
    });
}
