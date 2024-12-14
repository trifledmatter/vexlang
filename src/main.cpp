#include "main.h"

#include "listener.hpp"
#include "manager.hpp"
#include "response.hpp"

#include "commands/ping.hpp"
#include "commands/screen/print.hpp"
#include "commands/screen/printAt.hpp"
#include "commands/screen/clear.hpp"
#include "commands/screen/setColor.hpp"

#include <stdio.h>
#include <string.h>

void initialize() {
    pros::lcd::initialize();    
	update_screen("None", "None");

	commandManager.registerCommand(std::make_unique<PrintCommand>());
    commandManager.registerCommand(std::make_unique<PingCommand>());
    commandManager.registerCommand(std::make_unique<PrintAtCommand>());
    commandManager.registerCommand(std::make_unique<ClearCommand>());
    commandManager.registerCommand(std::make_unique<SetColorCommand>());

    pros::Task serial_task(listener, nullptr, "vexlang listener");
}
