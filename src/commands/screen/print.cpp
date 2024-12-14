#include "commands/screen/print.hpp"
#include "response.hpp"

PrintCommand::PrintCommand() 
    : Command("print", "ethan@trifledmatter.com", "Prints a message", "screen", 1.0f) {}

void PrintCommand::execute(const std::vector<std::string>& args) {
    if (args.empty()) {
        update_screen("NO MESSAGE PROVIDED", "None");
    } else {
        std::string message = join_arguments(args);
        update_screen("None", message);
        send_serial(message);
    }
}

std::string PrintCommand::join_arguments(const std::vector<std::string>& args) const {
    std::string result;
    for (const auto& arg : args) {
        if (!result.empty()) {
            result += " ";
        }
        result += arg;
    }
    return result;
}
