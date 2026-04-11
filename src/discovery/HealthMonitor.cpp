/*
 * Project: Aegis Governor V2.0
 * Author: Samarth
 * Description: Implementation of system CPU load monitoring via /proc/stat.
 */

#include "discovery/HealthMonitor.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>

namespace aegis {
namespace discovery {

void readCPUTicks(long long& activeTime, long long& totalTime) {
    std::ifstream file("/proc/stat");
    std::string line;
    std::getline(file, line);

    std::istringstream ss(line);
    std::string cpuLabel;
    ss >> cpuLabel;

    long long user, nice, system, idle, iowait, irq, softirq, steal;
    ss >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;

    long long idleTime = idle + iowait;
    activeTime = user + nice + system + irq + softirq + steal;
    totalTime = idleTime + activeTime;
}

double HealthMonitor::getSystemCPULoad() {
    long long active1, total1, active2, total2;

    readCPUTicks(active1, total1);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    readCPUTicks(active2, total2);

    long long activeDelta = active2 - active1;
    long long totalDelta = total2 - total1;

    if (totalDelta == 0) return 0.0;

    return 100.0 * static_cast<double>(activeDelta) / totalDelta;
}

}
}
