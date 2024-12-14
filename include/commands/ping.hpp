#ifndef PING_COMMAND_HPP
#define PING_COMMAND_HPP

#include "../command.hpp"

class PingCommand : public Command {
public:
    PingCommand();

    void execute(const std::vector<std::string>& args) override;
};

#endif