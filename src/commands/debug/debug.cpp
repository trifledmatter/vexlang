/**
 * This command is useless and filler atm while I figure out how I want to write this
 */

#include "commands/debug/debug.hpp"
#include <iostream>

DebugCommand::DebugCommand()
    : Command(
          "debug", 
          "ethan@trifledmatter.com", 
          "Manages debugging and diagnostics.", 
          "debug", 
          1.0),
      diagnosticResults("") {}

void DebugCommand::execute(const std::vector<std::string>& args) {
    if (args.empty()) {
        update_screen("Invalid arguments.", "Usage: vex debug <action>");
        return;
    }

    std::string action = args[0];

    if (action == "start") {
        handleDebugStart();
    } else if (action == "stop") {
        handleDebugStop();
    } else if (action == "run") {
        handleDiagnosticsRun();
    } else if (action == "getResults") {
        handleDiagnosticsGetResults();
    } else {
        handleInvalidAction(action);
    }
}

void DebugCommand::handleDebugStart() {
    send_serial("Debugging started.");
    update_screen("", "Debugging started.");
}

void DebugCommand::handleDebugStop() {
    send_serial("Debugging stopped.");
    update_screen("", "Debugging stopped.");
}

void DebugCommand::handleDiagnosticsRun() {
    diagnosticResults = "Diagnostics completed successfully.\n"
                        "Motor 1: OK\n"
                        "Sensor 2: OK\n"
                        "Battery: OK";

    send_serial("Diagnostics run completed.");
    update_screen("", "Diagnostics run completed.");
}

void DebugCommand::handleDiagnosticsGetResults() {
    if (diagnosticResults.empty()) {
        send_serial("No diagnostics results available. Run diagnostics first.");
        update_screen("No diagnostics results available.", "");
    } else {
        send_serial("Diagnostics Results:\n" + diagnosticResults);
        update_screen("", "Diagnostics results sent.");
    }
}

void DebugCommand::handleInvalidAction(const std::string& action) {
    update_screen("Unknown action '" + action + "'.", "Valid actions: start, stop, run, getResults.");
}
