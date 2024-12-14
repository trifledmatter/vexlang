#include "main.h"

#include "listener.hpp"
#include "manager.hpp"
#include "response.hpp"

#include "commands/ping.hpp"
#include "commands/screen/print.hpp"

#include <stdio.h>
#include <string.h>

void initialize() {
    pros::lcd::initialize();    
	update_screen("None", "None");

	commandManager.registerCommand(std::make_unique<PrintCommand>());
    commandManager.registerCommand(std::make_unique<PingCommand>());

    pros::Task serial_task(listener, nullptr, "vexlang listener");
}
