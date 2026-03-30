#include "discovery/HealthMonitor.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>

namespace aegis {
namespace discovery {

// Helper function to read the raw CPU ticks from /proc/stat
void readCPUTicks(long long& activeTime, long long& totalTime) {
    std::ifstream file("/proc/stat");
    std::string line;
    std::getline(file, line); // Read the first line which starts with "cpu"
    
    std::istringstream ss(line);
    std::string cpuLabel;
    ss >> cpuLabel; // Skip the word "cpu"
    
    // Read all the time metrics
    long long user, nice, system, idle, iowait, irq, softirq, steal;
    ss >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
    
    long long idleTime = idle + iowait;
    activeTime = user + nice + system + irq + softirq + steal;
    totalTime = idleTime + activeTime;
}

double HealthMonitor::getSystemCPULoad() {
    long long active1, total1, active2, total2;
    
    // 1. Take the first sample
    readCPUTicks(active1, total1);
    
    // 2. Pause the thread for 100 milliseconds
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // 3. Take the second sample
    readCPUTicks(active2, total2);
    
    // 4. Calculate the difference (delta)
    long long activeDelta = active2 - active1;
    long long totalDelta = total2 - total1;
    
    if (totalDelta == 0) return 0.0;
    
    // 5. Convert to a percentage
    return 100.0 * static_cast<double>(activeDelta) / totalDelta;
}

}
}
