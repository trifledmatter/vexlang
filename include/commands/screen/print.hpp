#ifndef PRINT_COMMAND_HPP
#define PRINT_COMMAND_HPP

#include "../command.hpp"

class PrintCommand : public Command {
public:
    PrintCommand();

    void execute(const std::vector<std::string>& args) override;

private:
    std::string join_arguments(const std::vector<std::string>& args) const;
};

#endif
