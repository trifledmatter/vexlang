#include "commands/screen/clear.hpp"
#include "response.hpp"
#include "errors.hpp"

ClearCommand::ClearCommand()
    : Command("clear", "ethan@trifledmatter.com", "Clears all responses", 1.0f) {}

void ClearCommand::execute(const std::vector<std::string> &args)
{
    handleErrors("Command Execution", [&]()
                 { update_screen("None", "None"); });
}
