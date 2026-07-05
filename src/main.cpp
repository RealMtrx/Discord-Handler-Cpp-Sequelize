#include "config.h"
#include "bot.h"
#include "handlers/anticrash.h"

int main() {
    handlers::setupAntiCrash();
    Config config = Config::load();
    Bot bot(config);
    bot.run();
    return 0;
}
