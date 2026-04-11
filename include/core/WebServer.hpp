/*
 * Project: Aegis Governor V2.0
 * Author: Samarth
 * Description: Header defining the web server interface for REST API and dashboard serving.
 */

#pragma once
#include "httplib.h"
#include "core/SystemState.hpp"
#include "control/DecisionEngine.hpp"
#include <memory>
#include <thread>

namespace aegis {
namespace core {

class WebServer {
private:
    httplib::Server svr;
    std::shared_ptr<SystemState> state;
    std::shared_ptr<control::DecisionEngine> engine;
    int port;

public:
    WebServer(std::shared_ptr<SystemState> sharedState, std::shared_ptr<control::DecisionEngine> decisionEngine, int port = 8080);
    void start();
    void stop();
};

}
}