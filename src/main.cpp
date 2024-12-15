#include "main.h"

#include "listener.hpp"
#include "manager.hpp"
#include "response.hpp"

// --- START COMMAND IMPORT ---

#include "commands/ping.hpp"

#include "commands/screen/print.hpp"
#include "commands/screen/printAt.hpp"
#include "commands/screen/clear.hpp"
#include "commands/screen/setColor.hpp"

#include "commands/sensor/sensor.hpp"

#include "commands/battery/battery.hpp"

#include "commands/motor/motor.hpp"

#include "commands/robot/robot.hpp"

// --- END COMMAND IMPORT ---

#include <stdio.h>
#include <string.h>

void initialize()
{
    pros::lcd::initialize();
    update_screen("None", "None");

    commandManager.registerCommand(std::make_unique<PingCommand>());
    commandManager.registerCommand(std::make_unique<PrintCommand>());
    commandManager.registerCommand(std::make_unique<PrintAtCommand>());
    commandManager.registerCommand(std::make_unique<ClearCommand>());
    commandManager.registerCommand(std::make_unique<SetColorCommand>());
    commandManager.registerCommand(std::make_unique<SensorCommand>());
    commandManager.registerCommand(std::make_unique<BatteryCommand>());
    commandManager.registerCommand(std::make_unique<RobotCommand>());
    commandManager.registerCommand(std::make_unique<MotorCommand>());

    // printf("<#>Debug Start<#>\n");

    // pros::Motor motor(1);
    // motor.move_velocity(10);
    // pros::delay(2000);
    // motor.move_velocity(0);

    pros::Task serial_task(listener, nullptr, "vexlang listener");
}
