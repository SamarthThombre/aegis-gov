/*
 * Project: Aegis Governor V2.0
 * Author: Samarth
 * Description: Header defining the logger interface for audit trail recording.
 */

#pragma once
#include <string>

namespace aegis {
namespace logging {

class Logger {
public:
    void logEvent(const std::string& message);
};

}
}
