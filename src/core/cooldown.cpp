#include "cooldown.h"

namespace core {

Cooldown::Cooldown(std::chrono::seconds duration)
    : duration_(duration) {}

bool Cooldown::isOnCooldown(dpp::snowflake userId) const {
    auto it = cooldowns_.find(userId);
    if (it == cooldowns_.end()) return false;
    auto now = std::chrono::steady_clock::now();
    if (now - it->second >= duration_) {
        cooldowns_.erase(it);
        return false;
    }
    return true;
}

void Cooldown::set(dpp::snowflake userId) {
    cooldowns_[userId] = std::chrono::steady_clock::now();
}

}
