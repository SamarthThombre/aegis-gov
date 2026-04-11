# Aegis Governor V2.0 🛡️

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![Platform](https://img.shields.io/badge/Platform-Linux-green.svg)](https://www.linux.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

## Project Overview

Aegis Governor V2.0 is a headless, cloud-native system execution guard designed for enterprise environments. It leverages POSIX signals and Linux Control Groups (CGroup V2) to pause or throttle rogue processes, ensuring system stability and resource management. The system is fully manageable via a thread-safe REST API and an intuitive Web Dashboard, making it ideal for automated governance in containerized or bare-metal deployments.

## Key Architectural Features

- **Thread-Safe Core Vault**: Utilizes `std::mutex` and `std::shared_ptr` for concurrent access to shared state, ensuring data integrity in multi-threaded environments.
- **Bi-Directional Action Queue**: Decouples the Web API from the Kernel Execution Engine, enabling asynchronous processing and improved responsiveness.
- **Native Linux Process Scanning**: Parses the `/proc` filesystem with multi-core CPU math normalization for accurate resource monitoring.
- **Kernel-Level Control**: Employs POSIX `SIGSTOP` and `SIGCONT` signals for precise process suspension and resumption.
- **CGroup V2 CPU Throttling**: Integrates with `/sys/fs/cgroup` to enforce CPU limits on processes, supporting fine-grained resource allocation.
- **Graceful Shutdown**: Intercepts `SIGINT` to automatically wake up "zombie" processes upon exit, preventing resource leaks.

## Installation & Build

### Prerequisites
- Linux operating system (tested on Ubuntu/Debian)
- CMake 3.16 or higher
- GCC 9+ or Clang 10+
- Root privileges for execution

### Build Steps
```bash
# Clone the repository
git clone https://github.com/your-repo/aegis-gov.git
cd aegis-gov

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the project
make -j$(nproc)
```

## Usage & Deployment

### Running the Application
Aegis Governor must be run with root privileges to access system resources:

```bash
sudo ./aegis_run
```

The application will start the REST API server and begin monitoring system processes.

### Accessing the Gateway Configuration Dashboard
Open your web browser and navigate to:
```
http://localhost:8080/
```

The dashboard provides real-time process monitoring, CPU usage visualization, and controls for pausing or capping processes.

### Setting Up as a Systemd Daemon
To run Aegis Governor as a system service:

1. Create a systemd service file `/etc/systemd/system/aegis-governor.service`:
   ```ini
   [Unit]
   Description=Aegis Governor V2.0 System Execution Guard
   After=network.target

   [Service]
   Type=simple
   User=root
   ExecStart=/path/to/aegis_run
   Restart=always
   RestartSec=5

   [Install]
   WantedBy=multi-user.target
   ```

2. Reload systemd and enable the service:
   ```bash
   sudo systemctl daemon-reload
   sudo systemctl enable aegis-governor
   sudo systemctl start aegis-governor
   ```

3. Check status:
   ```bash
   sudo systemctl status aegis-governor
   ```

## API Reference

### POST /api/action
Send control commands to processes.

**Example Request:**
```bash
curl -X POST http://localhost:8080/api/action \
  -H "Content-Type: application/json" \
  -d '{"pid": 1234, "type": "pause"}'
```

**Response:**
```json
{
  "success": true,
  "message": "Process paused successfully"
}
```

Supported actions: `pause`, `cap` (with optional `limit` parameter for CPU percentage).

For more API endpoints, refer to the `/api/status` for system information.
