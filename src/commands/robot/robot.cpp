#include "commands/robot/robot.hpp"
#include <stdexcept>

RobotCommand::RobotCommand()
    : Command(
          "robot", 
          "ethan@trifledmatter.com", 
          "Controls robot movement such as moving, turning, stopping, and resetting.", 
          "robot", 
          1.0) {}

void RobotCommand::execute(const std::vector<std::string>& args) {
    if (args.empty()) {
        update_screen("Invalid arguments.", "Usage: vex robot <action> <arguments>");
        return;
    }

    std::string action = args[0];

    if (action == "move") {
        handleMoveAction(std::vector<std::string>(args.begin() + 1, args.end()));
    } else if (action == "turn") {
        handleTurnAction(std::vector<std::string>(args.begin() + 1, args.end()));
    } else if (action == "stop") {
        handleStopAction();
    } else if (action == "reset") {
        handleResetAction();
    } else {
        update_screen("Unknown action '" + action + "'.", "Valid actions: move, turn, stop, reset.");
    }
}

void RobotCommand::handleMoveAction(const std::vector<std::string>& args) {
    if (args.size() < 4) {
        update_screen("Invalid arguments for move action.", "Usage: vex robot move <m1> <m2> <dist> <speed>");
        return;
    }

    int motor1 = parseMotorId(args[0]);
    int motor2 = parseMotorId(args[1]);
    int distance = parseArgument(args[2], "distance");
    int speed = parseArgument(args[3], "speed");

    if (motor1 == -1 || motor2 == -1 || distance == -1 || speed == -1) {
        return;
    }

    try {
        pros::Motor m1(motor1);
        pros::Motor m2(motor2);

        m1.move_relative(distance, speed);
        m2.move_relative(distance, speed);

        send_serial("Robot moving: motors " + std::to_string(motor1) + " and " + std::to_string(motor2) +
                    " for distance " + std::to_string(distance) + " at speed " + std::to_string(speed) + ".");
    } catch (...) {
        update_screen("Failed to move the robot.", "");
    }
}

void RobotCommand::handleTurnAction(const std::vector<std::string>& args) {
    if (args.size() < 4) {
        update_screen("Invalid arguments for turn action.", "Usage: vex robot turn <m1> <m2> <angle> <speed>");
        return;
    }

    int motor1 = parseMotorId(args[0]);
    int motor2 = parseMotorId(args[1]);
    int angle = parseArgument(args[2], "angle");
    int speed = parseArgument(args[3], "speed");

    if (motor1 == -1 || motor2 == -1 || angle == -1 || speed == -1) {
        return;
    }

    try {
        pros::Motor m1(motor1);
        pros::Motor m2(motor2);

        m1.move_relative(angle, speed);
        m2.move_relative(-angle, speed);

        send_serial("Robot turning: motors " + std::to_string(motor1) + " and " + std::to_string(motor2) +
                    " for angle " + std::to_string(angle) + " at speed " + std::to_string(speed) + ".");
    } catch (...) {
        update_screen("Failed to turn the robot.", "");
    }
}

void RobotCommand::handleStopAction() {
    try {
        for (int motorId = 1; motorId <= 21; ++motorId) {
            pros::Motor motor(motorId);
            motor.move_velocity(0);
        }

        send_serial("Robot stopped.");
    } catch (...) {
        update_screen("Failed to stop the robot.", "");
    }
}

void RobotCommand::handleResetAction() {
    try {
        for (int motorId = 1; motorId <= 21; ++motorId) {
            pros::Motor motor(motorId);
            motor.tare_position();
        }

        send_serial("Robot reset: motor encoders reset.");
    } catch (...) {
        update_screen("Failed to reset the robot.", "");
    }
}

int RobotCommand::parseMotorId(const std::string& motorIdStr) {
    try {
        int motorId = std::stoi(motorIdStr);
        if (motorId >= 1 && motorId <= 21) {
            return motorId;
        } else {
            update_screen("Invalid motor ID.", "Motor ID must be between 1 and 21.");
        }
    } catch (const std::invalid_argument&) {
        update_screen("Invalid motor ID format.", "Motor ID must be a number.");
    } catch (const std::out_of_range&) {
        update_screen("Motor ID out of range.", "Motor ID is too large.");
    }
    return -1;
}

int RobotCommand::parseArgument(const std::string& arg, const std::string& name) {
    try {
        int value = std::stoi(arg);
        return value;
    } catch (const std::invalid_argument&) {
        update_screen("Invalid " + name + " format.", name + " must be a number.");
    } catch (const std::out_of_range&) {
        update_screen(name + " out of range.", name + " is too large.");
    }
    return -1;
}
