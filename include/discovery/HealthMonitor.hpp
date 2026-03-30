#pragma once

namespace aegis {
namespace discovery {

class HealthMonitor {
public:
    // Calculates total system CPU load as a percentage (0.0 to 100.0)
    double getSystemCPULoad();
};

}
}
