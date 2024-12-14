#ifndef PING_COMMAND_HPP
#define PING_COMMAND_HPP

#include "../command.hpp"

class PingCommand : public Command {
public:
    PingCommand() : Command("ping", "Ethan", "Responds with pong", "misc", 1.0f) {}

    void execute(const std::vector<std::string>& args) override;
};

#endif