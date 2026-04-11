/*
 * Project: Aegis Governor V2.0
 * Author: Samarth
 * Description: Header defining the governor interface for process suspension and resumption.
 */

#pragma once

namespace aegis {
namespace control {

class Governor {
public:
    bool pauseProcess(int pid);
    bool resumeProcess(int pid);
};

}
}
