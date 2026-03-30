#pragma once

namespace aegis {
namespace control {

class Governor {
public:
    // Sends SIGSTOP to freeze a process
    bool pauseProcess(int pid);
    
    // Sends SIGCONT to unfreeze a process
    bool resumeProcess(int pid);
};

}
}
