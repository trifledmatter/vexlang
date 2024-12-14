#include "manager.hpp"

CommandManager commandManager;

void CommandManager::registerCommand(std::unique_ptr<Command> command) {
    std::string key = command->category + " " + command->name;
    commands[key] = std::move(command);
}

void CommandManager::executeCommand(const std::string& key, const std::vector<std::string>& args) {
    if (commands.find(key) != commands.end()) {
        commands[key]->execute(args);
    } else {
        std::cout << "Command not found: " << key << std::endl;
    }
}

void CommandManager::showCommands() {
    for (const auto& command : commands) {
        command.second->showInfo();
    }
}
