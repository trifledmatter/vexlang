#ifndef MOTOR_COMMAND_HPP
#define MOTOR_COMMAND_HPP

#include "command.hpp"
#include "response.hpp"
#include "pros/motors.hpp"
#include <string>
#include <vector>

class MotorCommand : public Command
{
public:
    MotorCommand();

    void execute(const std::vector<std::string> &args) override;

private:
    int parseMotorId(const std::string &motorIdStr);
    void handleSetAction(int motorId, const std::vector<std::string> &args);
    void handleStopAction(int motorId);
    void handleSetDirectionAction(int motorId, const std::vector<std::string> &args);
    void handleSetPositionAction(int motorId, const std::vector<std::string> &args);
    void handleSetPowerAction(int motorId, const std::vector<std::string> &args);
    void handleHoldAction(int motorId, const std::vector<std::string> &args);
    void handleAllStopAction();
    void handleInvalidAction(const std::string &action);
};

#endif
