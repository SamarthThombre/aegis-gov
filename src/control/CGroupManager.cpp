/*
 * Project: Aegis Governor V2.0
 * Author: Samarth
 * Description: Implementation of CPU throttling using Linux CGroup V2.
 */

#include "control/CGroupManager.hpp"
#include <iostream>
#include <sstream>

namespace aegis {
namespace control {

bool CGroupManager::capProcess(int pid, int limitPercentage) {
    try {
        std::string cgroupPath = "/sys/fs/cgroup/aegis_limit_" + std::to_string(pid);
        std::filesystem::create_directory(cgroupPath);

        std::ofstream procsFile(cgroupPath + "/cgroup.procs");
        if (!procsFile.is_open()) {
            std::cerr << "Failed to open cgroup.procs for PID " << pid << std::endl;
            return false;
        }
        procsFile << pid << std::endl;
        procsFile.close();

        int quota = (limitPercentage * 1000);
        std::string cpuMaxValue = std::to_string(quota) + " 100000";

        std::ofstream cpuMaxFile(cgroupPath + "/cpu.max");
        if (!cpuMaxFile.is_open()) {
            std::cerr << "Failed to open cpu.max for PID " << pid << std::endl;
            return false;
        }
        cpuMaxFile << cpuMaxValue << std::endl;
        cpuMaxFile.close();

        return true;
    } catch (const std::exception& e) {
        std::cerr << "Exception in capProcess for PID " << pid << ": " << e.what() << std::endl;
        return false;
    }
}

}
}