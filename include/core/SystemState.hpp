/*
 * Project: Aegis Governor V2.0
 * Author: Samarth
 * Description: Header defining the system state management with thread-safe access.
 */

#pragma once
#include <vector>
#include <string>
#include <mutex>
#include "discovery/ProcScanner.hpp"

namespace aegis {
namespace core {

enum class ActionType {
    PAUSE,
    CAP
};

struct ActionCommand {
    int targetPid;
    ActionType type;
    int limitPercentage = 0;
};

class SystemState {
private:
    double currentCPULoad;
    double currentThreshold;
    std::vector<discovery::ProcessInfo> activeProcesses;
    std::vector<std::string> recentLogs;
    mutable std::mutex stateMutex;

public:
    SystemState(double initialThreshold);

    void updateCPULoad(double load);
    void updateThreshold(double threshold);
    void updateProcesses(const std::vector<discovery::ProcessInfo>& processes);
    void addLog(const std::string& logMessage);

    double getCPULoad() const;
    double getThreshold() const;
    std::vector<discovery::ProcessInfo> getProcesses() const;
    std::vector<std::string> getLogs() const;
};

}
}
