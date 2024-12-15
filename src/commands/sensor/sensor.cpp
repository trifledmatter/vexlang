#include "commands/sensor/sensor.hpp"
#include "errors.hpp"
#include <stdexcept>

SensorCommand::SensorCommand()
    : Command(
          "sensor",
          "ethan@trifledmatter.com",
          "Controls sensor actions such as get reading, calibrate, reset, etc.",
          1.0) {}

void SensorCommand::execute(const std::vector<std::string> &args)
{
    handleErrors("SensorCommand Execution", [&]()
                 {
        if (args.size() < 2) {
            update_screen("Invalid arguments.", "Usage: vex sensor <s> <action>");
            send_serial("Error: Invalid arguments.");
            return;
        }

        int sensorId = -1;
        if (args[0] != "all") {
            try {
                sensorId = std::stoi(args[0]);
            } catch (const std::invalid_argument &) {
                update_screen("Invalid sensor ID format.", "Sensor ID must be a number.");
                send_serial("Error: Invalid sensor ID format.");
                return;
            } catch (const std::out_of_range &) {
                update_screen("Sensor ID out of range.", "Sensor ID is too large.");
                send_serial("Error: Sensor ID out of range.");
                return;
            }
        } else {
            sensorId = -2;
        }

        if (sensorId != -2 && (sensorId < 1 || sensorId > 8)) {
            update_screen("Invalid sensor ID.", "Sensor ID must be between 1 and 8.");
            send_serial("Error: Invalid sensor ID range.");
            return;
        }

        std::string action = args[1];

        if (action == "getReading") {
            handleGetReadingAction(sensorId);
        } else if (action == "calibrate") {
            handleCalibrateAction(sensorId);
        } else if (action == "reset") {
            if (sensorId == -2) {
                handleAllResetAction();
            } else {
                handleResetAction(sensorId);
            }
        } else {
            handleInvalidAction(action);
        } });
}

void SensorCommand::handleGetReadingAction(int sensorId)
{
    if (sensorId < 1 || sensorId > 8)
    {
        update_screen("Invalid sensor port.", "Sensor ID must be between 1 and 8.");
        send_serial("Error: Invalid sensor port " + std::to_string(sensorId));
        return;
    }

    try
    {
        pros::adi::AnalogIn sensor(sensorId);
        int reading = sensor.get_value();
        send_serial("Sensor " + std::to_string(sensorId) + " reading: " + std::to_string(reading));
        update_screen("Sensor Reading", "Sensor " + std::to_string(sensorId) + ": " + std::to_string(reading));
    }
    catch (...)
    {
        update_screen("Failed to get sensor reading.", "Unknown error.");
        send_serial("Error: Unknown failure in getReading.");
    }
}

void SensorCommand::handleCalibrateAction(int sensorId)
{
    if (sensorId < 1 || sensorId > 8)
    {
        update_screen("Invalid sensor port.", "Sensor ID must be between 1 and 8.");
        send_serial("Error: Invalid sensor port " + std::to_string(sensorId));
        return;
    }

    try
    {
        pros::adi::AnalogIn sensor(sensorId);
        sensor.calibrate();
        send_serial("Sensor " + std::to_string(sensorId) + " calibrated.");
        update_screen("Sensor Calibrated", "Sensor " + std::to_string(sensorId));
    }
    catch (...)
    {
        update_screen("Failed to calibrate sensor.", "Unknown error.");
        send_serial("Error: Unknown failure in calibrate.");
    }
}

void SensorCommand::handleResetAction(int sensorId)
{
    if (sensorId < 1 || sensorId > 8)
    {
        update_screen("Invalid sensor port.", "Sensor ID must be between 1 and 8.");
        send_serial("Error: Invalid sensor port " + std::to_string(sensorId));
        return;
    }

    try
    {
        pros::adi::AnalogIn sensor(sensorId);
        sensor.calibrate();
        send_serial("Sensor " + std::to_string(sensorId) + " reset.");
        update_screen("Sensor Reset", "Sensor " + std::to_string(sensorId));
    }
    catch (...)
    {
        update_screen("Failed to reset sensor.", "Unknown error.");
        send_serial("Error: Unknown failure in reset.");
    }
}

void SensorCommand::handleAllResetAction()
{
    for (int sensorId = 1; sensorId <= 8; ++sensorId)
    {
        try
        {
            pros::adi::AnalogIn sensor(sensorId);
            sensor.calibrate();
        }
        catch (...)
        {
            send_serial("Error resetting sensor " + std::to_string(sensorId));
            update_screen("Error resetting sensor " + std::to_string(sensorId), "");
        }
    }
    send_serial("All sensors reset.");
    update_screen("All Sensors Reset", "Success.");
}

void SensorCommand::handleInvalidAction(const std::string &action)
{
    update_screen("Unknown action '" + action + "'.", "Valid actions: getReading, calibrate, reset.");
    send_serial("Error: Unknown action '" + action + "'.");
}
