#include "main.h"
#include "pros/screen.hpp"

#include "commands/ping.hpp"

#include <stdio.h>

void PingCommand::execute(const std::vector<std::string>& args) {
    pros::lcd::initialize();
    pros::lcd::set_text(3, "Executing ping command...");

    printf("PONG!\n");

}
