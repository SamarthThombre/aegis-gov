/*
 * Project: Aegis Governor V2.0
 * Author: Samarth
 * Description: Header defining the decision engine interface for process control and governance.
 */

#pragma once
#include "discovery/ProcScanner.hpp"
#include "discovery/HealthMonitor.hpp"
#include "control/Governor.hpp"
#include "control/CGroupManager.hpp"
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
    CGroupManager cgroupManager;
    logging::Logger logger;
    std::shared_ptr<core::SystemState> state;
    std::atomic<bool> running;

public:
    DecisionEngine(std::shared_ptr<core::SystemState> sharedState);
    void run();
    void stop();
    bool pauseProcess(int pid);
    bool executeCommand(const core::ActionCommand& command);
};

}
}