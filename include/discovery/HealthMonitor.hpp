/*
 * Project: Aegis Governor V2.0
 * Author: Samarth
 * Description: Header defining the health monitor interface for system CPU load measurement.
 */

#pragma once

namespace aegis {
namespace discovery {

class HealthMonitor {
public:
    double getSystemCPULoad();
};

}
}
