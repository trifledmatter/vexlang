#ifndef CLEAR_COMMAND_HPP
#define CLEAR_COMMAND_HPP

#include "command.hpp"

class ClearCommand : public Command {
public:
    ClearCommand();

    void execute(const std::vector<std::string>& args) override;
};

#endif
