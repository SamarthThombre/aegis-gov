#pragma once
#include <string>
#include <fstream>
#include <filesystem>

namespace aegis {
namespace control {

class CGroupManager {
public:
    bool capProcess(int pid, int limitPercentage);
};

}
}