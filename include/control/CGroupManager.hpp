/*
 * Project: Aegis Governor V2.0
 * Author: Samarth
 * Description: Header defining the CGroup manager interface for CPU throttling.
 */

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