#include "commands/screen/clear.hpp"
#include "response.hpp"

ClearCommand::ClearCommand() 
    : Command("clear", "System", "Clears all responses", "screen", 1.0f) {}

void ClearCommand::execute(const std::vector<std::string>& args) {
    update_screen("None", "None");
}
