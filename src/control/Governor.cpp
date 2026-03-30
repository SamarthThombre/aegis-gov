#include "control/Governor.hpp"
#include <signal.h> // POSIX library for system signals

namespace aegis {
namespace control {

bool Governor::pauseProcess(int pid) {
    // kill() returns 0 if the signal was successfully sent
    if (kill(pid, SIGSTOP) == 0) {
        return true;
    }
    return false; // Failed (usually means we don't have permission, or PID died)
}

bool Governor::resumeProcess(int pid) {
    if (kill(pid, SIGCONT) == 0) {
        return true;
    }
    return false;
}

}
}
