#include "commands/sensor/sensor.hpp"
#include <stdexcept>
#include <climits>

SensorCommand::SensorCommand()
    : Command(
          "vex sensor", 
          "ethan@trifledmatter.com", 
          "Controls sensor actions such as get reading, calibrate, reset, etc.", 
          "sensor", 
          1.0) {}

void SensorCommand::execute(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        update_screen("Invalid arguments.", "Usage: vex sensor <s> <action> <arguments>");
        return;
    }

    int sensorId = (args[0] == "all") ? -2 : parseSensorId(args[0]);

    if (sensorId == -1) {
        update_screen("Invalid sensor ID.", "");
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
    }
}

int SensorCommand::parseSensorId(const std::string& sensorIdStr) {
    try {
        int sensorId = std::stoi(sensorIdStr);
        if (sensorId >= 1 && sensorId <= 21) {
            return sensorId;
        } else {
            update_screen("Invalid sensor ID.", "Sensor ID must be between 1 and 21.");
        }
    } catch (const std::invalid_argument&) {
        update_screen("Invalid sensor ID format.", "Sensor ID must be a number.");
    } catch (const std::out_of_range&) {
        update_screen("Sensor ID out of range.", "Sensor ID is too large.");
    }
    return -1;
}

void SensorCommand::handleGetReadingAction(int sensorId) {
    try {
        pros::ADIAnalogIn sensor(sensorId);
        int reading = sensor.get_value();

        send_serial("Sensor " + std::to_string(sensorId) + " reading: " + std::to_string(reading));
    } catch (...) {
        update_screen("Failed to get sensor reading.", "");
    }
}

void SensorCommand::handleCalibrateAction(int sensorId) {
    try {
        pros::ADIAnalogIn sensor(sensorId);
        sensor.calibrate();

        send_serial("Sensor " + std::to_string(sensorId) + " calibrated.");
    } catch (...) {
        update_screen("Failed to calibrate sensor.", "");
    }
}

void SensorCommand::handleResetAction(int sensorId) {
    try {
        pros::ADIAnalogIn sensor(sensorId);
        sensor.reset();

        send_serial("Sensor " + std::to_string(sensorId) + " reset.");
    } catch (...) {
        update_screen("Failed to reset sensor.", "");
    }
}

void SensorCommand::handleAllResetAction() {
    for (int sensorId = 1; sensorId <= 21; ++sensorId) {
        try {
            pros::ADIAnalogIn sensor(sensorId);
            sensor.reset();
        } catch (...) {
            update_screen("Error resetting sensor " + std::to_string(sensorId) + ".", "");
        }
    }

    send_serial("Success: All sensors reset.");
}

void SensorCommand::handleInvalidAction(const std::string& action) {
    update_screen("Unknown action '" + action + "'.", "Valid actions: getReading, calibrate, reset, setRange.");
}
