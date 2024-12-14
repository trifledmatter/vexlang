#include "main.h"
#include "listener.hpp"
#include "manager.hpp"

#include <stdio.h>
#include <string.h>

void initialize() {
    pros::lcd::initialize();
    // pros::lcd::set_text(1, "Hello PROS User!");

    commandManager.registerCommand(std::make_unique<PingCommand>());

    pros::Task serial_task(listener, nullptr, "vexlang listener");
}
