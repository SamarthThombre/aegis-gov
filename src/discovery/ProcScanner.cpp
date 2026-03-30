#include "discovery/ProcScanner.hpp"
#include <filesystem>
#include <fstream>
#include <algorithm>

namespace fs = std::filesystem;

namespace aegis {
namespace discovery {

std::vector<ProcessInfo> ProcScanner::getActiveProcesses() {
    std::vector<ProcessInfo> processes;
    
    for (const auto& entry : fs::directory_iterator("/proc")) {
        if (entry.is_directory()) {
            std::string dirName = entry.path().filename().string();
            
            if (std::all_of(dirName.begin(), dirName.end(), ::isdigit)) {
                int pid = std::stoi(dirName);
                std::string name = "unknown";
                
                // Read the 'comm' file to get the exact process name
                std::ifstream commFile("/proc/" + dirName + "/comm");
                if (commFile.is_open()) {
                    std::getline(commFile, name);
                }
                
                processes.push_back({pid, name});
            }
        }
    }
    return processes;
}

}
}
