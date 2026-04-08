#include "core/WebServer.hpp"
#include <sstream>
#include <iomanip>

namespace aegis {
namespace core {

WebServer::WebServer(std::shared_ptr<SystemState> sharedState, std::shared_ptr<control::DecisionEngine> decisionEngine, int p) 
    : state(sharedState), engine(decisionEngine), port(p) {
    

    // The "Home Route" - Serves the Gateway Configuration UI from the project root
    svr.Get("/", [&](const httplib::Request& req, httplib::Response& res) {
        std::ifstream file("index.html");
        if (!file.is_open()) {
            file.open("../index.html");
        }

        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            res.set_content(buffer.str(), "text/html");
        } else {
            res.status = 404;
            res.set_content("Gateway UI Offline: index.html not found. Please run the server from the project root or place index.html next to the executable.", "text/plain");
        }
    });

    svr.Get("/index.html", [&](const httplib::Request& req, httplib::Response& res) {
        std::ifstream file("index.html");
        if (!file.is_open()) {
            file.open("../index.html");
        }

        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            res.set_content(buffer.str(), "text/html");
        } else {
            res.status = 404;
            res.set_content("Gateway UI Offline: index.html not found. Please run the server from the project root or place index.html next to the executable.", "text/plain");
        }
    });
        
    // Define the /api/status endpoint
    svr.Get("/api/status", [&](const httplib::Request&, httplib::Response& res) {
        auto processes = state->getProcesses();
        std::stringstream ss;
        ss << "{"
           << "\"cpuLoad\": " << state->getCPULoad() << ","
           << "\"activeThreshold\": " << state->getThreshold() << ","
           << "\"activeProcesses\": [";
        for (size_t i = 0; i < processes.size(); ++i) {
            ss << "{\"pid\": " << processes[i].pid << ", \"name\": \"" << processes[i].name << "\", \"cpuUsage\": " << std::fixed << std::setprecision(1) << processes[i].cpuUsage << "}";
            if (i < processes.size() - 1) ss << ",";
        }
        ss << "]}";
        
        res.set_content(ss.str(), "application/json");
        // Allow the browser to access this from a different port (CORS)
        res.set_header("Access-Control-Allow-Origin", "*");
    });

    

    // Define the /api/action endpoint
    svr.Post("/api/action", [&](const httplib::Request& req, httplib::Response& res) {
        // Parse JSON for {"pid": number, "type": "pause"|"cap", "limit": number}
        std::string body = req.body;
        core::ActionCommand command;
        command.targetPid = -1;
        command.limitPercentage = 0;

        // Extract pid
        size_t pidPos = body.find("\"pid\":");
        if (pidPos != std::string::npos) {
            size_t start = pidPos + 6;
            size_t end = body.find(",", start);
            if (end == std::string::npos) end = body.find("}", start);
            std::string pidStr = body.substr(start, end - start);
            command.targetPid = std::stoi(pidStr);
        }

        // Extract type
        size_t typePos = body.find("\"type\":\"");
        if (typePos != std::string::npos) {
            size_t start = typePos + 8;
            size_t end = body.find("\"", start);
            std::string typeStr = body.substr(start, end - start);
            if (typeStr == "pause") {
                command.type = core::ActionType::PAUSE;
            } else if (typeStr == "cap") {
                command.type = core::ActionType::CAP;
            }
        }

        // Extract limit for cap
        size_t limitPos = body.find("\"limit\":");
        if (limitPos != std::string::npos) {
            size_t start = limitPos + 8;
            size_t end = body.find(",", start);
            if (end == std::string::npos) end = body.find("}", start);
            std::string limitStr = body.substr(start, end - start);
            command.limitPercentage = std::stoi(limitStr);
        }

        if (command.targetPid != -1) {
            if (engine->executeCommand(command)) {
                res.set_content("{\"status\": \"success\"}", "application/json");
            } else {
                res.set_content("{\"status\": \"error\", \"message\": \"Failed to execute command\"}", "application/json");
            }
        } else {
            res.set_content("{\"status\": \"error\", \"message\": \"Invalid request\"}", "application/json");
        }
        res.set_header("Access-Control-Allow-Origin", "*");
    });

    // Define the /api/config endpoint
    svr.Post("/api/config", [&](const httplib::Request& req, httplib::Response& res) {
        // Parse JSON for {"threshold": double}
        std::string body = req.body;
        size_t thresholdPos = body.find("\"threshold\":");
        if (thresholdPos != std::string::npos) {
            size_t start = thresholdPos + 12;
            size_t end = body.find(",", start);
            if (end == std::string::npos) end = body.find("}", start);
            std::string thresholdStr = body.substr(start, end - start);
            double newThreshold = std::stod(thresholdStr);
            state->updateThreshold(newThreshold);
            res.set_content("{\"status\": \"success\"}", "application/json");
        } else {
            res.set_content("{\"status\": \"error\", \"message\": \"Invalid request\"}", "application/json");
        }
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
