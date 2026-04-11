/*
 * Project: Aegis Governor V2.0
 * Author: Samarth
 * Description: Main entry point initializing the system state, decision engine, and web server.
 */

#include <iostream>
#include <thread>
#include <memory>
#include "core/SystemState.hpp"
#include "control/DecisionEngine.hpp"
#include "core/WebServer.hpp"

int main() {
    auto sharedState = std::make_shared<aegis::core::SystemState>(80.0);

    auto engine = std::make_shared<aegis::control::DecisionEngine>(sharedState);
    std::thread engineThread(&aegis::control::DecisionEngine::run, engine);
    engineThread.detach();

    std::cout << "=== Aegis V2.0 Cloud-Native Backend ===\n";
    std::cout << "[Web] API available at http://localhost:8080/api/status\n";

    aegis::core::WebServer webServer(sharedState, engine, 8080);

    std::thread diagnosticThread([sharedState]() {
        while (true) {
            std::cout << "[Diagnostic] Vault CPU: " << sharedState->getCPULoad() << "% | PIDs: " << sharedState->getProcesses().size() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    });
    diagnosticThread.detach();

    webServer.start();
    return 0;
}