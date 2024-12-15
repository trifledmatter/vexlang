#include "commands/screen/printAt.hpp"
#include "response.hpp"
#include "errors.hpp"

PrintAtCommand::PrintAtCommand()
    : Command("printAt", "ethan@trifledmatter.com", "Prints message at specified coordinates", 1.0f) {}

void PrintAtCommand::execute(const std::vector<std::string> &args)
{
    handleErrors("Command Execution", [&]()
                 {
                     if (args.size() < 2)
                     {
                         update_screen("INSUFFICIENT ARGUMENTS", "Provide y, and message.");
                         return;
                     }

                     int y = std::stoi(args[0]);

                     std::string message = join_arguments(std::vector<std::string>(args.begin() + 1, args.end()));

                     pros::lcd::print(y, "%s", message);
                     std::string response = "Printed message at ( Line: " + std::to_string(y) + " )";
                     send_serial(response); });
}

std::string PrintAtCommand::join_arguments(const std::vector<std::string> &args) const
{
    std::string result;
    for (const auto &arg : args)
    {
        if (!result.empty())
        {
            result += " ";
        }
        result += arg;
    }
    return result;
}
