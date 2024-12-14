#include "commands/motor/motor.hpp"

#include <stdexcept>
#include <climits>

MotorCommand::MotorCommand()
    : Command(
          "motor", 
          "ethan@trifledmatter.com", 
          "Controls motor actions such as set speed, stop, etc.", 
          "motor", 
          1.0) {}

void MotorCommand::execute(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        update_screen("Invalid arguments.", "Usage: vex motor <m> <action> <arguments>");
        return;
    }

    int motorId = (args[0] == "all") ? -2 : parseMotorId(args[0]);

    if (motorId == -1) {
        update_screen("Invalid motor ID.", "");
        return;
    }

    std::string action = args[1];

    if (action == "set") {
        handleSetAction(motorId, std::vector<std::string>(args.begin() + 2, args.end()));
    } else if (action == "stop") {
        if (motorId == -2) {
            handleAllStopAction();
        } else {
            handleStopAction(motorId);
        }
    } else if (action == "setDirection") {
        handleSetDirectionAction(motorId, std::vector<std::string>(args.begin() + 2, args.end()));
    } else if (action == "setPosition") {
        handleSetPositionAction(motorId, std::vector<std::string>(args.begin() + 2, args.end()));
    } else if (action == "setPower") {
        handleSetPowerAction(motorId, std::vector<std::string>(args.begin() + 2, args.end()));
    } else {
        handleInvalidAction(action);
    }
}

int MotorCommand::parseMotorId(const std::string& motorIdStr) {
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

void MotorCommand::handleSetAction(int motorId, const std::vector<std::string>& args) {
    if (args.empty()) {
        update_screen("Missing speed argument for set action.", "");
        return;
    }

    try {
        int speed = std::stoi(args[0]);
        if (speed < -200 || speed > 200) {
            update_screen("Speed must be between -200 and 200.", "");
            return;
        }

        pros::Motor motor(motorId);
        motor.move_velocity(speed);

        send_serial("Success: Motor " + std::to_string(motorId) + " set to speed " + std::to_string(speed) + ".");
    } catch (...) {
        update_screen("Invalid speed value.", "");
    }
}

void MotorCommand::handleStopAction(int motorId) {
    try {
        pros::Motor motor(motorId);
        motor.move_velocity(0);

        send_serial("Success: Motor " + std::to_string(motorId) + " stopped.");
    } catch (...) {
        update_screen("Failed to stop motor.", "");
    }
}

void MotorCommand::handleSetDirectionAction(int motorId, const std::vector<std::string>& args) {
    if (args.empty()) {
        update_screen("Missing direction argument for setDirection action.", "");
        return;
    }

    std::string direction = args[0];
    try {
        pros::Motor motor(motorId);
        if (direction == "forward") {
            motor.set_reversed(false);
        } else if (direction == "reverse") {
            motor.set_reversed(true);
        } else {
            update_screen("Invalid direction. Use 'forward' or 'reverse'.", "");
            return;
        }

        send_serial("Success: Motor " + std::to_string(motorId) + " direction set to " + direction + ".");
    } catch (...) {
        update_screen("Failed to set motor direction.", "");
    }
}

void MotorCommand::handleSetPositionAction(int motorId, const std::vector<std::string>& args) {
    if (args.empty()) {
        update_screen("Missing position argument for setPosition action.", "");
        return;
    }

    try {
        int position = std::stoi(args[0]);

        pros::Motor motor(motorId);
        motor.move_absolute(position, 100); // just assume a velocity of 100

        send_serial("Success: Motor " + std::to_string(motorId) + " moved to position " + std::to_string(position) + ".");
    } catch (...) {
        update_screen("Invalid position value.", "");
    }
}

void MotorCommand::handleSetPowerAction(int motorId, const std::vector<std::string>& args) {
    if (args.empty()) {
        update_screen("Missing power argument for setPower action.", "");
        return;
    }

    try {
        int power = std::stoi(args[0]);
        if (power < -127 || power > 127) {
            update_screen("Power must be between -127 and 127.", "");
            return;
        }

        pros::Motor motor(motorId);
        motor.move(power);

        send_serial("Success: Motor " + std::to_string(motorId) + " power set to " + std::to_string(power) + ".");
    } catch (...) {
        update_screen("Invalid power value.", "");
    }
}

void MotorCommand::handleAllStopAction() {
    for (int motorId = 1; motorId <= 21; ++motorId) {
        try {
            pros::Motor motor(motorId);
            motor.move_velocity(0);
        } catch (...) {
            update_screen("Error stopping motor " + std::to_string(motorId) + ".", "");
        }
    }

    send_serial("Success: All motors stopped.");
}

void MotorCommand::handleInvalidAction(const std::string& action) {
    update_screen("Unknown action '" + action + "'.", "Valid actions: set, stop, setDirection, setPosition, setPower.");
}
