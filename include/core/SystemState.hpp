#pragma once
#include <vector>
#include <string>
#include <mutex>
#include "discovery/ProcScanner.hpp"

namespace aegis {
namespace core {

class SystemState {
private:
    double currentCPULoad;
    double currentThreshold;
    std::vector<discovery::ProcessInfo> activeProcesses;
    std::vector<std::string> recentLogs;
    
    // The lock that protects all the variables above
    mutable std::mutex stateMutex;

public:
    SystemState(double initialThreshold);

    // --- Setters (The Writers) ---
    void updateCPULoad(double load);
    void updateThreshold(double threshold);
    void updateProcesses(const std::vector<discovery::ProcessInfo>& processes);
    void addLog(const std::string& logMessage);

    // --- Getters (The Readers) ---
    double getCPULoad() const;
    double getThreshold() const;
    std::vector<discovery::ProcessInfo> getProcesses() const;
    std::vector<std::string> getLogs() const;
};

}
}
