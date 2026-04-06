#include "core/WebServer.hpp"
#include <sstream>

namespace aegis {
namespace core {

WebServer::WebServer(std::shared_ptr<SystemState> sharedState, int p) 
    : state(sharedState), port(p) {
    
    // Define the /api/status endpoint
    svr.Get("/api/status", [&](const httplib::Request&, httplib::Response& res) {
        std::stringstream ss;
        ss << "{"
           << "\"cpu_load\": " << state->getCPULoad() << ","
           << "\"threshold\": " << state->getThreshold() << ","
           << "\"process_count\": " << state->getProcesses().size()
           << "}";
        
        res.set_content(ss.str(), "application/json");
        // Allow the browser to access this from a different port (CORS)
        res.set_header("Access-Control-Allow-Origin", "*");
    });
}

void WebServer::start() {
    state->addLog("Web Server starting on port " + std::to_string(port));
    svr.listen("0.0.0.0", port);
}

void WebServer::stop() {
    svr.stop();
}

}
}
