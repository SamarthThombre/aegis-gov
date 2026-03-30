#pragma once
#include <vector>
#include <string>

namespace aegis {
namespace discovery {

// Create a custom struct to hold both pieces of data
struct ProcessInfo {
    int pid;
    std::string name;
};

class ProcScanner {
public:
    // Now returns our custom struct instead of just integers
    std::vector<ProcessInfo> getActiveProcesses();
};

}
}
