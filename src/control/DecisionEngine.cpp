#include "control/DecisionEngine.hpp"
#include <thread>
#include <chrono>

namespace aegis {
namespace control {

DecisionEngine::DecisionEngine(std::shared_ptr<core::SystemState> sharedState) 
    : state(sharedState), running(true) {}

void DecisionEngine::run() {
    state->addLog("Engine Started: Background monitoring active.");

    while (running) {
        // 1. Collect Telemetry
        double currentLoad = monitor.getSystemCPULoad();
        auto processes = scanner.getActiveProcesses();

        // 2. Silently update the Vault
        state->updateCPULoad(currentLoad);
        state->updateProcesses(processes);

        // 3. Logic Check (The Governor)
        if (currentLoad > state->getThreshold()) {
            state->addLog("ALERT: CPU Spike detected at " + std::to_string(currentLoad) + "%");
            
            // Whitelist Logic
            std::vector<std::string> whitelist = {"systemd", "bash", "aegis_run", "sshd"};
            
            for (const auto& proc : processes) {
                bool isImmune = false;
                for (const auto& safe : whitelist) {
                    if (proc.name == safe) { isImmune = true; break; }
                }

                if (!isImmune && proc.name == "stress") {
                    if (governor.pauseProcess(proc.pid)) {
                        state->addLog("ACTION: Suspended process " + proc.name + " (PID: " + std::to_string(proc.pid) + ")");
                        logger.logEvent("Governor suspended PID " + std::to_string(proc.pid));
                    }
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void DecisionEngine::stop() {
    running = false;
}

}
}