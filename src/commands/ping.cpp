#include "main.h"
#include "pros/screen.hpp"

#include "response.hpp"
#include "commands/ping.hpp"

#include <stdio.h>

void PingCommand::execute(const std::vector<std::string>& args) {
    pros::lcd::initialize();
    update_screen("None", "PONG!");

    printf("PONG!\n");

}
