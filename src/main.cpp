#include <iostream>
#include <thread>
#include <memory>
#include "core/SystemState.hpp"
#include "control/DecisionEngine.hpp"
#include "core/WebServer.hpp"

int main()
{
    auto sharedState = std::make_shared<aegis::core::SystemState>(80.0);

    // 1. Start the Core Engine (Background Thread)
    aegis::control::DecisionEngine engine(sharedState);
    std::thread engineThread(&aegis::control::DecisionEngine::run, &engine);
    engineThread.detach();

    // 2. Start the Web Server (Main Thread)
    std::cout << "=== Aegis V2.0 Cloud-Native Backend ===\n";
    std::cout << "[Web] API available at http://localhost:8080/api/status\n";

    // ... inside main ...
    aegis::core::WebServer webServer(sharedState, 8080);

    // Start a simple logger thread to see if the engine is actually updating the vault
    std::thread diagnosticThread([sharedState]()
                                 {
    while (true) {
        std::cout << "[Diagnostic] Vault CPU: " << sharedState->getCPULoad() << "% | PIDs: " << sharedState->getProcesses().size() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    } });
    diagnosticThread.detach();

    webServer.start();
    return 0;
}