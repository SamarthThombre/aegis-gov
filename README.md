# Aegis Governor: Automated System Execution Guard

Aegis is a high-performance, multi-threaded C++ systems tool designed for Linux (WSL2) environments. It acts as an automated "Governor," monitoring system-wide CPU pressure and proactively managing rogue or high-intensity processes to ensure core system stability.



## 🛠️ Core Features
* **Automated Discovery Engine:** Recursively scans the `/proc` virtual filesystem to map active Process IDs (PIDs) and their human-readable application names.
* **Real-Time Health Monitor:** Parses `/proc/stat` to calculate precise CPU load deltas using a 100ms sampling window.
* **Immunity Whitelisting:** Features a built-in safety layer to protect critical system infrastructure (e.g., `systemd`, `ssh`, `bash`) from accidental suspension.
* **Execution Governor:** Interfaces directly with the Linux kernel via POSIX signals (`SIGSTOP`) to freeze non-compliant processes.
* **Dynamic Command Center:** A thread-safe, interactive dashboard that allows administrators to update CPU thresholds live without restarting the service.
* **Forensic Audit Logging:** Generates an immutable `aegis_audit.log` for post-event analysis and system compliance tracking.

## 🏗️ Technical Architecture
The project follows a modular C++17 architecture:
* **Discovery:** Filesystem interaction and process mapping.
* **Control:** POSIX signal handling and decision-making logic.
* **Logging:** Thread-safe file I/O for event auditing.

## 🚀 Getting Started

### Prerequisites
* C++17 Compatible Compiler (GCC/Clang)
* CMake 3.10+
* Linux Environment (Native or WSL2)

### Build Instructions
```bash
mkdir build
cd build
cmake ..
make
```

Usage

Launch the Governor:
    ```bash

    ./aegis_run
    
Trigger a System Spike (Stress Test):
    In a separate terminal, run the included multi-threaded stress tool to watch Aegis detect and neutralize the threat:
    ```Bash

    ./stress
    
    
###📊 Project Significance

This project demonstrates advanced proficiency in Systems Programming, Concurrency (Multi-threading), and Resource Governance. It serves as a technical proof-of-concept for automated risk mitigation in server-side environments.
