#pragma once
#include <vector>
#include <string>

namespace aegis {
namespace discovery {

// Create a custom struct to hold both pieces of data
struct ProcessInfo {
    int pid;
    std::string name;
    double cpuUsage = 0.0;
};

class ProcScanner {
public:
    // Now returns our custom struct instead of just integers
    std::vector<ProcessInfo> getActiveProcesses();
};

}
}
