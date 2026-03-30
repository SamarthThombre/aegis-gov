#include "control/DecisionEngine.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>

namespace aegis {
namespace control {

DecisionEngine::DecisionEngine(double threshold) : cpuThreshold(threshold), running(true) {}

void DecisionEngine::inputListener() {
    // This loop runs in the background
    while (running) {
        std::string input;
        std::getline(std::cin, input);
        
        if (!input.empty()) {
            try {
                // Try to convert what you typed into a decimal number
                double newThreshold = std::stod(input);
                cpuThreshold = newThreshold;
                logger.logEvent("System Admin updated threshold to " + std::to_string(newThreshold) + "%");
            } catch (...) {
                // If you typed letters by mistake, just ignore it and keep running
            }
        }
    }
}

void DecisionEngine::run() {
    logger.logEvent("Aegis Governor Initialized. Threshold: " + std::to_string(cpuThreshold) + "%");
    
    // Launch the listener thread and detach it so it runs independently
    std::thread listener(&DecisionEngine::inputListener, this);
    listener.detach(); 

    while (running) {
        double currentLoad = monitor.getSystemCPULoad();
        
        // ANSI Escape Codes: \033[2J clears the screen, \033[1;1H moves cursor to top-left
        std::cout << "\033[2J\033[1;1H";
        
        std::cout << "=== AEGIS GOVERNOR DASHBOARD ===\n";
        std::cout << "Monitoring CPU every 2 seconds.\n";
        std::cout << "--------------------------------\n";
        std::cout << "Current Threshold : " << cpuThreshold << "%\n";
        std::cout << "System CPU Load   : " << currentLoad << "%\n";
        std::cout << "--------------------------------\n";
        std::cout << "Type a new number and press Enter to change threshold live.\n\n";

if (currentLoad > cpuThreshold) {
            std::cout << "[!] ALERT: CPU threshold exceeded!\n";
            
            // 1. Get the newly upgraded process list
            std::vector<discovery::ProcessInfo> processes = scanner.getActiveProcesses();
            
            // 2. Define the Immunity Whitelist (System Critical + Aegis itself)
            std::vector<std::string> whitelist = {
                "systemd", "init", "bash", "sshd", "wsl", "aegis_run"
            };

            int targetCount = 0;
            std::string targetNames = "";

            // 3. Filter out the immune processes
            for (const auto& proc : processes) {
                bool isImmune = false;
                for (const auto& safeName : whitelist) {
                    if (proc.name == safeName) {
                        isImmune = true;
                        break;
                    }
                }
                
                // If it is NOT immune, it becomes a target
                if (!isImmune) {
                    targetCount++;
                    if (targetCount <= 3) { 
                        targetNames += proc.name + " ";
                    }
                    
                    // --- THE SAFETY IS OFF ---
                    // For our live-fire test, explicitly target the stress program
                    if (proc.name == "stress") {
                        std::cout << "[!] FIRING SIGSTOP AT PID " << proc.pid << " (" << proc.name << ")\n";
                        governor.pauseProcess(proc.pid);
                        logger.logEvent("ACTION: Suspended " + proc.name + " (PID: " + std::to_string(proc.pid) + ")");
                    }
                }
            }

            std::cout << "[*] Scanned " << processes.size() << " total processes.\n";
            std::cout << "[*] Identified " << targetCount << " non-immune targets.\n";
            std::cout << "[*] Top targets: " << targetNames << "...\n";
            std::cout << "[*] Protective action logged to aegis_audit.log\n";
            
            logger.logEvent("SPIKE DETECTED: CPU at " + std::to_string(currentLoad) + "%. Targets found: " + std::to_string(targetCount) + " (" + targetNames + ")");
        }

std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

}
}
