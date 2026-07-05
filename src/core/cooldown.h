#pragma once
#include <dpp/dpp.h>
#include <unordered_map>
#include <chrono>

namespace core {

class Cooldown {
public:
    explicit Cooldown(std::chrono::seconds duration);

    bool isOnCooldown(dpp::snowflake userId) const;
    void set(dpp::snowflake userId);

private:
    std::chrono::seconds duration_;
    mutable std::unordered_map<dpp::snowflake, std::chrono::steady_clock::time_point> cooldowns_;
};

}
