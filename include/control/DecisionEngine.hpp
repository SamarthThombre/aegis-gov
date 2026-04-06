#pragma once
#include "discovery/ProcScanner.hpp"
#include "discovery/HealthMonitor.hpp"
#include "control/Governor.hpp"
#include "logging/Logger.hpp"
#include "core/SystemState.hpp"
#include <atomic>
#include <memory>

namespace aegis {
namespace control {

class DecisionEngine {
private:
    discovery::ProcScanner scanner;
    discovery::HealthMonitor monitor;
    Governor governor;
    logging::Logger logger;
    
    // Pointer to our shared vault
    std::shared_ptr<core::SystemState> state;
    
    std::atomic<bool> running;

public:
    // The engine now takes a pointer to the shared state
    DecisionEngine(std::shared_ptr<core::SystemState> sharedState);
    void run();
    void stop();
};

}
}