#include "anticrash.h"
#include <csignal>
#include <iostream>
#include <cstdlib>

namespace {

void signalHandler(int signal) {
    std::cerr << "[AntiCrash] Caught signal " << signal << std::endl;
    std::exit(signal);
}

[[noreturn]] void exceptionHandler() {
    try {
        throw;
    } catch (const std::exception& e) {
        std::cerr << "[AntiCrash] Unhandled exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "[AntiCrash] Unknown unhandled exception" << std::endl;
    }
    std::exit(1);
}

}

void handlers::setupAntiCrash() {
    std::signal(SIGSEGV, signalHandler);
    std::signal(SIGABRT, signalHandler);
    std::signal(SIGFPE, signalHandler);
    std::signal(SIGILL, signalHandler);
    std::set_terminate(exceptionHandler);
    std::cout << "[AntiCrash] Handlers installed" << std::endl;
}
