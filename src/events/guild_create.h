#pragma once
#include <dpp/dpp.h>

inline void OnGuildCreate(dpp::cluster& client) {
    client.on_guild_create([](const dpp::guild_create_t& event) {
        dpp::log(dpp::loglevel::ll_debug,
            "Joined guild: " + event.created->name);
    });
}
