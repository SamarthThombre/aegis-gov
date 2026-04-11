/*
 * Project: Aegis Governor V2.0
 * Author: Samarth
 * Description: Stress testing utility to simulate high CPU load for governor validation.
 */

#include <iostream>
#include <vector>
#include <thread>

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

    unsigned int numCores = std::thread::hardware_concurrency();
    if (numCores == 0) numCores = 4;

    std::cout << "Igniting " << numCores << " CPU cores...\n";

    std::vector<std::thread> threads;
    for (unsigned int i = 0; i < numCores; ++i) {
        threads.push_back(std::thread(burnCPU));
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
