/*
 * Project: Aegis Governor V2.0
 * Author: Samarth
 * Description: Implementation of process suspension and resumption using POSIX signals.
 */

#include "control/Governor.hpp"
#include <signal.h>

namespace aegis {
namespace control {

bool Governor::pauseProcess(int pid) {
    return kill(pid, SIGSTOP) == 0;
}

bool Governor::resumeProcess(int pid) {
    return kill(pid, SIGCONT) == 0;
}

}
}
