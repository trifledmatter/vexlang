#include "main.h"
#include "pros/screen.hpp"

#include "response.hpp"
#include "commands/ping.hpp"
#include "errors.hpp"

#include <stdio.h>

PingCommand::PingCommand()
    : Command("ping", "ethan@trifledmatter.com", "Pong!", 1.0f) {}

void PingCommand::execute(const std::vector<std::string> &args)
{
    handleErrors("Command Execution", [&]()
                 {pros::lcd::initialize();
    update_screen("None", "PONG!");

    printf("PONG!\n"); });
}
