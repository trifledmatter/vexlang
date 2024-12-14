#include "commands/screen/setColor.hpp"
#include "response.hpp"

SetColorCommand::SetColorCommand() 
    : Command("setColor", "System", "Sets screen color (pen or eraser)", "screen", 1.0f) {}

void SetColorCommand::execute(const std::vector<std::string>& args) {
    if (args.empty()) {
        update_screen("NO COLOR PROVIDED", "None");
        return;
    }

    std::string color_name = args[0];
    pros::Color color;

    if (color_name == "red") {
        color = pros::Color::red;
    } else if (color_name == "green") {
        color = pros::Color::green;
    } else if (color_name == "blue") {
        color = pros::Color::blue;
    } else if (color_name == "yellow") {
        color = pros::Color::yellow;
    } else if (color_name == "white") {
        color = pros::Color::white;
    } else if (color_name == "black") {
        color = pros::Color::black;
    } else {
        update_screen("INVALID COLOR", "None");
        return;
    }

    pros::screen::set_pen(color);
    pros::screen::set_eraser(color);

    std::string response = "Color set to " + color_name;
    update_screen("None", response);
    send_serial(response);
}
