#include "webhooks.h"

namespace core {

Webhook::Webhook(dpp::cluster& client, dpp::snowflake channelId)
    : client_(client), channelId_(channelId) {}

void Webhook::send(const std::string& content) {
    dpp::message msg(channelId_, content);
    client_.message_create(msg);
}

void Webhook::sendEmbed(const dpp::embed& embed) {
    dpp::message msg(channelId_, "");
    msg.add_embed(embed);
    client_.message_create(msg);
}

}
