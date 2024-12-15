#include "commands/battery/battery.hpp"
#include "pros/misc.hpp"
#include "errors.hpp"
#include <stdexcept>

BatteryCommand::BatteryCommand()
    : Command(
          "battery",
          "ethan@trifledmatter.com",
          "Retrieves information and diagnostics about the battery.",
          1.0) {}

void BatteryCommand::execute(const std::vector<std::string> &args)
{
    handleErrors("Command Execution", [&]()
                 {
        if (args.empty()) {
        update_screen("Invalid arguments.", "Usage: vex battery <action>");
        return;
        }

        std::string action = args[0];

        if (action == "getVoltage") {
            handleGetVoltage();
        } else if (action == "getCapacity") {
            handleGetCapacity();
        } else if (action == "getTemperature") {
            handleGetTemperature();
        } else if (action == "getDiagnostics") {
            handleGetDiagnostics();
        } else {
            handleInvalidAction(action);
        } });
}

void BatteryCommand::handleGetVoltage()
{
    try
    {
        int voltage = pros::battery::get_voltage(); // millivolts
        float voltageInVolts = voltage / 1000.0f;   // conv. to volts

        send_serial("Battery Voltage: " + std::to_string(voltageInVolts) + "V");
        update_screen("", "Voltage: " + std::to_string(voltageInVolts) + "V");
    }
    catch (...)
    {
        update_screen("Failed to get battery voltage.", "");
    }
}

void BatteryCommand::handleGetCapacity()
{
    try
    {
        int capacity = pros::battery::get_capacity(); // %

        send_serial("Battery Capacity: " + std::to_string(capacity) + "%");
        update_screen("", "Capacity: " + std::to_string(capacity) + "%");
    }
    catch (...)
    {
        update_screen("Failed to get battery capacity.", "");
    }
}

void BatteryCommand::handleGetTemperature()
{
    try
    {
        int temperature = pros::battery::get_temperature(); // Degrees Celsius

        send_serial("Battery Temperature: " + std::to_string(temperature) + "°C");
        update_screen("", "Temperature: " + std::to_string(temperature) + "°C");
    }
    catch (...)
    {
        update_screen("Failed to get battery temperature.", "");
    }
}

void BatteryCommand::handleGetDiagnostics()
{
    try
    {
        int voltage = pros::battery::get_voltage();
        float voltageInVolts = voltage / 1000.0f;

        int capacity = pros::battery::get_capacity();
        int temperature = pros::battery::get_temperature();

        std::string diagnostics = "Battery Diagnostics:\n";
        diagnostics += "Voltage: " + std::to_string(voltageInVolts) + "V\n";
        diagnostics += "Capacity: " + std::to_string(capacity) + "%\n";
        diagnostics += "Temperature: " + std::to_string(temperature) + "°C";

        send_serial(diagnostics);
        update_screen("", "Diagnostics sent.");
    }
    catch (...)
    {
        update_screen("Failed to retrieve battery diagnostics.", "");
    }
}

void BatteryCommand::handleInvalidAction(const std::string &action)
{
    update_screen("Unknown action '" + action + "'.", "Valid actions: getVoltage, getCapacity, getTemperature, getDiagnostics.");
}
