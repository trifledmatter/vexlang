#ifndef SENSOR_COMMAND_HPP
#define SENSOR_COMMAND_HPP

#include "command.hpp"
#include "response.hpp"
#include "pros/sensors.hpp"
#include <string>
#include <vector>

class SensorCommand : public Command {
public:
    SensorCommand();

    void execute(const std::vector<std::string>& args) override;

private:
    int parseSensorId(const std::string& sensorIdStr);
    void handleGetReadingAction(int sensorId);
    void handleCalibrateAction(int sensorId);
    void handleResetAction(int sensorId);
    void handleAllResetAction();
    void handleInvalidAction(const std::string& action);
};

#endif
