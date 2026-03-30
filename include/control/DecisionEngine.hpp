#pragma once
#include "discovery/ProcScanner.hpp"
#include "discovery/HealthMonitor.hpp"
#include "control/Governor.hpp"
#include "logging/Logger.hpp"
#include <atomic>

namespace aegis {
namespace control {

class DecisionEngine {
private:
    discovery::ProcScanner scanner;
    discovery::HealthMonitor monitor;
    Governor governor;
    logging::Logger logger;
    
    // std::atomic ensures it's safe to change this variable across different threads
    std::atomic<double> cpuThreshold;
    std::atomic<bool> running;

    // The background function that listens for your keyboard input
    void inputListener(); 

public:
    DecisionEngine(double threshold = 80.0);
    void run();
};

}
}
