#pragma once
#include <string>

namespace aegis {
namespace logging {

class Logger {
public:
    // Writes a timestamped message to aegis_audit.log
    void logEvent(const std::string& message);
};

}
}
