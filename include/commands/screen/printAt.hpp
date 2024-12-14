#ifndef PRINT_AT_COMMAND_HPP
#define PRINT_AT_COMMAND_HPP

#include "command.hpp"
#include "pros/screen.hpp"
#include "main.h"

class PrintAtCommand : public Command {
public:
    PrintAtCommand();

    void execute(const std::vector<std::string>& args) override;
private:
    std::string join_arguments(const std::vector<std::string>& args) const;
};

#endif
