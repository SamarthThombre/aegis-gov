/*
 * Project: Aegis Governor V2.0
 * Author: Samarth
 * Description: Header defining the process scanning interface for discovering active system processes.
 */

#pragma once
#include <vector>
#include <string>

namespace aegis {
namespace discovery {

struct ProcessInfo {
    int pid;
    std::string name;
    double cpuUsage = 0.0;
};

class ProcScanner {
public:
    std::vector<ProcessInfo> getActiveProcesses();
};

}
}
