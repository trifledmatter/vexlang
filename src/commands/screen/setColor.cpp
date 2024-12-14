#include "setColor.hpp"
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
        color = pros::Color::RED;
    } else if (color_name == "green") {
        color = pros::Color::GREEN;
    } else if (color_name == "blue") {
        color = pros::Color::BLUE;
    } else if (color_name == "yellow") {
        color = pros::Color::YELLOW;
    } else if (color_name == "white") {
        color = pros::Color::WHITE;
    } else if (color_name == "black") {
        color = pros::Color::BLACK;
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
