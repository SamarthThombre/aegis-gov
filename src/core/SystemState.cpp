#include "core/SystemState.hpp"

namespace aegis {
namespace core {

SystemState::SystemState(double initialThreshold) 
    : currentCPULoad(0.0), currentThreshold(initialThreshold) {}

// --- Writers ---
void SystemState::updateCPULoad(double load) {
    std::lock_guard<std::mutex> lock(stateMutex);
    currentCPULoad = load;
}

void SystemState::updateThreshold(double threshold) {
    std::lock_guard<std::mutex> lock(stateMutex);
    currentThreshold = threshold;
}

void SystemState::updateProcesses(const std::vector<discovery::ProcessInfo>& processes) {
    std::lock_guard<std::mutex> lock(stateMutex);
    activeProcesses = processes;
}

void SystemState::addLog(const std::string& logMessage) {
    std::lock_guard<std::mutex> lock(stateMutex);
    recentLogs.push_back(logMessage);
    // Keep only the last 10 logs in memory to prevent infinite growth
    if (recentLogs.size() > 10) {
        recentLogs.erase(recentLogs.begin());
    }
}

// --- Readers ---
double SystemState::getCPULoad() const {
    std::lock_guard<std::mutex> lock(stateMutex);
    return currentCPULoad;
}

double SystemState::getThreshold() const {
    std::lock_guard<std::mutex> lock(stateMutex);
    return currentThreshold;
}

std::vector<discovery::ProcessInfo> SystemState::getProcesses() const {
    std::lock_guard<std::mutex> lock(stateMutex);
    return activeProcesses;
}

std::vector<std::string> SystemState::getLogs() const {
    std::lock_guard<std::mutex> lock(stateMutex);
    return recentLogs;
}

}
}
