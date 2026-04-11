/*
 * Project: Aegis Governor V2.0
 * Author: Samarth
 * Description: Implementation of audit logging to file with timestamps.
 */

#include "logging/Logger.hpp"
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>

namespace aegis {
namespace logging {

void Logger::logEvent(const std::string& message) {
    std::ofstream file("aegis_audit.log", std::ios_base::app);
    if (file.is_open()) {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        file << "[" << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") << "] " << message << "\n";
    }
}

}
}
