#pragma once
#include "httplib.h"
#include "core/SystemState.hpp"
#include <memory>
#include <thread>

namespace aegis {
namespace core {

class WebServer {
private:
    httplib::Server svr;
    std::shared_ptr<SystemState> state;
    int port;

public:
    WebServer(std::shared_ptr<SystemState> sharedState, int port = 8080);
    void start();
    void stop();
};

}
}