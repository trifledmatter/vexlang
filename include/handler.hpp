#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "main.h"
#include "manager.hpp"

#include "commands/ping.hpp"

#include "pros/serial.hpp"
#include "pros/screen.hpp"

#include <vector>
#include <string>
#include <iostream>

std::vector<std::string> tokenize(const char* message);

void handler(const char* message);


#endif