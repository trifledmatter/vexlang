#include "main.h"

#include "response.hpp"

#include "pros/serial.hpp"
#include "pros/screen.hpp"

#include <algorithm>
#include <string>

void send_serial(const std::string& message) {
    std::string formattedMessage = message;
    std::transform(formattedMessage.begin(), formattedMessage.end(), formattedMessage.begin(), ::toupper);

    formattedMessage = "<#" + formattedMessage + "#>";

    printf("%s", formattedMessage.c_str());
}

void update_screen(const std::string& errors = "None", const std::string& response = "None") {
    std::string err = errors;
    std::string resp = response;

    err = ">    - " + err;
    resp = ">    - " + resp;
    
    pros::lcd::set_text(0, "> Errors:");
    pros::lcd::set_text(1, err);
    pros::lcd::set_text(2, "");
    pros::lcd::set_text(3, "> Response");
    pros::lcd::set_text(4, resp);
    pros::lcd::set_text(5, "");
    pros::lcd::set_text(6, "> github.com/trifledmatter/vexlang");
    pros::lcd::set_text(7, "> Made with <3 by Ethan");
}