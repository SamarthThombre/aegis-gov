#include <iostream>
#include <vector>
#include <thread>

// This function forces a CPU core to work at 100% capacity
void burnCPU() {
    while (true) {
        double math = 0.0;
        for (int i = 0; i < 1000000; ++i) {
            math += i * 3.14159;
        }
    }
}

int main() {
    std::cout << "🔥 INITIATING C++ STRESS TEST 🔥\n";
    std::cout << "Press Ctrl+C to stop the burn.\n\n";
    
    // Find out how many CPU cores your machine has
    unsigned int numCores = std::thread::hardware_concurrency();
    if (numCores == 0) numCores = 4; // Fallback
    
    std::cout << "Igniting " << numCores << " CPU cores...\n";
    
    // Launch a thread for every core
    std::vector<std::thread> threads;
    for (unsigned int i = 0; i < numCores; ++i) {
        threads.push_back(std::thread(burnCPU));
    }
    
    // Keep the main program running
    for (auto& t : threads) {
        t.join();
    }
    
    return 0;
}
