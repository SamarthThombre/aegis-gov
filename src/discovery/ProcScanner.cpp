#include "discovery/ProcScanner.hpp"
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <unistd.h>
#include <sstream>

namespace fs = std::filesystem;

namespace aegis {
namespace discovery {

std::vector<ProcessInfo> ProcScanner::getActiveProcesses() {
    std::vector<ProcessInfo> processes;
    
    // Read system uptime
    double uptime = 0.0;
    std::ifstream uptimeFile("/proc/uptime");
    if (uptimeFile.is_open()) {
        uptimeFile >> uptime;
    }
    
    long hertz = sysconf(_SC_CLK_TCK);
    
    for (const auto& entry : fs::directory_iterator("/proc")) {
        if (entry.is_directory()) {
            std::string dirName = entry.path().filename().string();
            
            if (std::all_of(dirName.begin(), dirName.end(), ::isdigit)) {
                int pid = std::stoi(dirName);
                std::string name = "unknown";
                double cpuUsage = 0.0;
                
                // Read the 'comm' file to get the exact process name
                std::ifstream commFile("/proc/" + dirName + "/comm");
                if (commFile.is_open()) {
                    std::getline(commFile, name);
                }
                
                // Read /proc/[pid]/stat to calculate CPU usage
                std::ifstream statFile("/proc/" + dirName + "/stat");
                if (statFile.is_open()) {
                    std::string line;
                    std::getline(statFile, line);
                    std::istringstream iss(line);
                    std::string token;
                    int field = 1;
                    long utime = 0, stime = 0, starttime = 0;
                    while (iss >> token) {
                        if (field == 14) utime = std::stol(token);
                        else if (field == 15) stime = std::stol(token);
                        else if (field == 22) starttime = std::stol(token);
                        field++;
                    }
                    
                    double totalTime = (utime + stime) / (double)hertz;
                    double secondsActive = uptime - (starttime / (double)hertz);
                    if (secondsActive > 0) {
                        cpuUsage = 100.0 * (totalTime / secondsActive);
                    }
                }
                
                processes.push_back({pid, name, cpuUsage});
            }
        }
    }
    return processes;
}

}
}
