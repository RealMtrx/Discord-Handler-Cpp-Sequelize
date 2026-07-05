#pragma once
#include <dpp/dpp.h>
#include <string>

namespace core {

class Webhook {
public:
    Webhook(dpp::cluster& client, dpp::snowflake channelId);
    void send(const std::string& content);
    void sendEmbed(const dpp::embed& embed);

private:
    dpp::cluster& client_;
    dpp::snowflake channelId_;
};

}
