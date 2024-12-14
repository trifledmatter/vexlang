#ifndef BATTERY_COMMAND_HPP
#define BATTERY_COMMAND_HPP

#include "command.hpp"
#include "response.hpp"
#include <string>
#include <vector>

class BatteryCommand : public Command {
public:
    BatteryCommand();

    void execute(const std::vector<std::string>& args) override;

private:
    void handleGetVoltage();
    void handleGetCapacity();
    void handleGetTemperature();
    void handleGetDiagnostics();
    void handleInvalidAction(const std::string& action);
};

#endif
