#ifndef COMMAND_MANAGER_HPP
#define COMMAND_MANAGER_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include "command.hpp"

// ---- Include Command Headers Here ----

#include "commands/ping.hpp"

// ---- End Include Commands Headers ----

class CommandManager {
public:
    std::map<std::string, std::unique_ptr<Command>> commands;

    void registerCommand(std::unique_ptr<Command> command);
    void executeCommand(const std::string& key, const std::vector<std::string>& args);
    void showCommands();
};

extern CommandManager commandManager;

#endif
