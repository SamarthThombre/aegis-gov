/*
 * Project: Aegis Governor V2.0
 * Author: Samarth
 * Description: Implementation of thread-safe system state management.
 */

#include "core/SystemState.hpp"

namespace aegis {
namespace core {

SystemState::SystemState(double initialThreshold)
    : currentCPULoad(0.0), currentThreshold(initialThreshold) {}

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
    if (recentLogs.size() > 10) {
        recentLogs.erase(recentLogs.begin());
    }
}

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
