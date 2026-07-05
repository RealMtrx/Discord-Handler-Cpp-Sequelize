#pragma once
#include <dpp/dpp.h>

inline void OnReady(dpp::cluster& client) {
    client.on_ready([&client](const dpp::ready_t&) {
        dpp::log(dpp::loglevel::ll_info,
            "Bot is ready! Logged in as " + client.me.username);
    });
}
