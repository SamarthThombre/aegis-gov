cmake_minimum_required(VERSION 3.10)
project(AegisGovernor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ... (Keep the top part the same) ...
include_directories(include)

# Tell the compiler about the new Logger file
add_executable(aegis_run 
    src/main.cpp 
    src/discovery/ProcScanner.cpp 
    src/discovery/HealthMonitor.cpp 
    src/control/Governor.cpp 
    src/control/DecisionEngine.cpp 
    src/control/CGroupManager.cpp 
    src/logging/Logger.cpp 
    src/core/SystemState.cpp 
    src/core/WebServer.cpp
)

# Find the Linux threading library
find_package(Threads REQUIRED)

# Link the threading library to BOTH your main app and your stress test
target_link_libraries(aegis_run Threads::Threads)
target_include_directories(aegis_run PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_executable(stress src/stress.cpp)
target_link_libraries(stress Threads::Threads)
