#ifndef DEBUG_COMMAND_HPP
#define DEBUG_COMMAND_HPP

#include "command.hpp"
#include "response.hpp"
#include <string>
#include <vector>

class DebugCommand : public Command {
public:
    DebugCommand();
    void execute(const std::vector<std::string>& args) override;

private:
    void handleDebugStart();
    void handleDebugStop();
    void handleDiagnosticsRun();
    void handleDiagnosticsGetResults();
    void handleInvalidAction(const std::string& action);
    std::string diagnosticResults;
};

#endif
