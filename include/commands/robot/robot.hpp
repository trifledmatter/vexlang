#ifndef ROBOT_COMMAND_HPP
#define ROBOT_COMMAND_HPP

#include "command.hpp"
#include "response.hpp"
#include "pros/motors.hpp"
#include <string>
#include <vector>

class RobotCommand : public Command {
public:
    RobotCommand();

    void execute(const std::vector<std::string>& args) override;

private:
    void handleMoveAction(const std::vector<std::string>& args);
    void handleTurnAction(const std::vector<std::string>& args);
    void handleStopAction();
    void handleResetAction();
    int parseMotorId(const std::string& motorIdStr);
    int parseArgument(const std::string& arg, const std::string& name);
};

#endif
